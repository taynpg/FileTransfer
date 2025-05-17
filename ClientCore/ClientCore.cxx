#include "ClientCore.h"

ClientCore::ClientCore(asio::io_context& ioContext) : socket_(ioContext)
{
}

bool ClientCore::Connect(const std::string& ip, int port)
{
    try {
        asio::ip::tcp::resolver resolver(ioContext_);
        auto ep = resolver.resolve(ip, std::to_string(port));
        asio::connect(socket_, ep);
        cf_->Info(tr("Connected to server {}:{} success."), ip, port);
        return true;
    } catch (const std::exception& ex) {
        cf_->Error(tr("Connect to server {}:{} failed. {}"), ip, port,
                   ex.what());
        return false;
    }
}

void ClientCore::Disconnect()
{
    if (socket_.is_open()) {
        socket_.shutdown(asio::ip::tcp::socket::shutdown_both);
        socket_.close();
    }
}

bool ClientCore::Send(FrameBuffer* frame)
{
    if (frame == nullptr) {
        return false;
    }
    char* od = nullptr;
    int odLen = 0;
    if (!Protocol::PackBuffer(frame, &od, odLen)) {
        return false;
    }
    auto ret = Send(od, odLen);
    delete[] od;
    return ret;
}

void ClientCore::SetUserInterface(
    const std::shared_ptr<ClientUserInterface>& cf)
{
    cf_ = cf;
}

bool ClientCore::Send(const char* data, int len)
{
    try {
        asio::write(socket_, asio::buffer(data, len));
        return true;
    } catch (const std::exception& ex) {
        cf_->Error(tr("Send data to server failed. {}"), ex.what());
        return false;
    }
}

void ClientCore::Recv()
{
    auto self(shared_from_this());
    socket_.async_read_some(
        asio::buffer(recvBuffer_),
        [this, self](const std::error_code& ec, std::size_t len) {
            if (!ec) {
                mutBuffer_.Push(recvBuffer_.data(), len);
                while (true) {
                    auto* frame = Protocol::ParseBuffer(mutBuffer_);
                    if (frame == nullptr) {
                        break;
                    }
                    UseFrame(frame);
                    delete frame;
                }
                return;
            }
            cf_->Error(tr("Receive data from server failed. {}"), ec.message());
        });
}

void ClientCore::UseFrame(FrameBuffer* frame)
{
}
