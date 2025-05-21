#include "Server.h"

Server::Server(asio::io_context& io_context, const std::shared_ptr<spdlog::logger>& logger)
    : io_context_(io_context), acceptor_(io_context), logger_(logger)
{
}

Server::~Server()
{
    thRun_ = false;
    if (monitorTh_.joinable()) {
        monitorTh_.join();
    }
}

void Server::Accept()
{
    auto sockPtr = std::make_shared<asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*sockPtr, [this, sockPtr](const asio::error_code& ec) {
        if (!ec) {
            auto endPoint = sockPtr->remote_endpoint();
            auto id = endPoint.address().to_string() + ":" + std::to_string(endPoint.port());
            bool allowConnect = false;
            {
                std::unique_lock<std::shared_mutex> lock(cliMut_);
                if (clientMap_.size() >= 100) {
                    logger_->warn("Client Connected: {} but not allow", id);
                    sockPtr->close();
                } else {
                    logger_->info("Client Connected: {}", id);
                    auto client = std::make_shared<TranClient>();
                    client->mSock = sockPtr;
                    client->onlineTime =
                        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                            .count();
                    client->name = id;
                    client->lastRecvTime = std::chrono::high_resolution_clock::now();
                    clientMap_.emplace(id, client);
                    allowConnect = true;
                }
            }
            if (allowConnect) {
                clientThread_.emplace(id, std::thread([this, sockPtr, id]() { thClientThread(sockPtr, id); }));
            } else {
                std::this_thread::sleep_for(std::chrono::minutes(1));
            }
        }
        Accept();
    });
}

bool Server::Run(int32_t port)
{
    asio::ip::tcp::resolver resolver(io_context_);
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
    try {
        acceptor_.open(endpoint.protocol());
        acceptor_.bind(endpoint);
        acceptor_.listen();
    } catch (const asio::system_error& e) {
        logger_->error("Server::Run: {}", e.what());
        return false;
    }
    auto bound_endpoint = acceptor_.local_endpoint();
    id_ = bound_endpoint.address().to_string() + ":" + std::to_string(bound_endpoint.port());
    logger_->info("Server Running On: {}", id_);
    Accept();
    return true;
}

void Server::thClientThread(const sockPtr& sockPtr, const std::string& id)
{
    std::shared_ptr<int> deleter(new int(0), [this, id](int* p) {
        std::unique_lock<std::shared_mutex> lock(cliMut_);
        clientMap_.erase(id);
        if (clientThread_.count(id)) {
            clientThread_[id].detach();
            clientThread_.erase(id);
        }
        logger_->info("Client Disconnected: {}", id);
        delete p;
    });

    std::shared_ptr<TranClient> client;
    {
        std::shared_lock<std::shared_mutex> lock(cliMut_);
        client = clientMap_[id];
    }
    if (!client) {
        logger_->error("Server::thClientThread: client not found {}", id);
        return;
    }

    asio::error_code ec;
    while (thRun_) {
        try {
            size_t len = sockPtr->read_some(asio::buffer(client->buf.data(), client->buf.size()), ec);
            if (ec) {
                logger_->error("Server::thClientThread: read_some error {}", ec.message());
                break;
            }
            client->buffer.Push(client->buf.data(), len);
        } catch (const std::exception& e) {
            logger_->error("Server recv data exception {}", e.what());
            break;
        }
        while (true) {
            auto* frame = Protocol::ParseBuffer(client->buffer);
            if (!frame) {
                break;
            }
            frame->fid = id;
            if (frame->dataType <= 30) {
                frame->tid = id_;
                ReplyRequest(sockPtr, frame);
                delete frame;
                continue;
            }
            Forward(client->mSock, frame);
            delete frame;
        }
    }
}

bool Server::Forward(const sockPtr& sockPtr, FrameBuffer* frame)
{
    return false;
}

void Server::ReplyRequest(const sockPtr& sockPtr, FrameBuffer* frame)
{
}

bool Server::Send(const sockPtr& sockPtr, FrameBuffer* frame)
{
    if (!frame) {
        return false;
    }
    char* od = nullptr;
    int odLen = 0;
    if (!Protocol::PackBuffer(frame, &od, odLen)) {
        return false;
    }
    try {
        sockPtr->send(asio::buffer(od, odLen));
        delete[] od;
        return true;
    } catch (const std::exception& e) {
        logger_->error("Server send failed, {}", e.what());
        delete[] od;
        return false;
    }
}
