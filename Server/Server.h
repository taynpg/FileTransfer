#ifndef CONSOLE_H
#define CONSOLE_H

#include <InfoCommunicate.hpp>
#include <Protocol.h>
#include <asio.hpp>
#include <cstdint>
#include <globalDefine.h>
#include <memory>
#include <shared_mutex>
#include <unordered_map>

#include "SimpleLog.hpp"

using highClock_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
using sockPtr = std::shared_ptr<asio::ip::tcp::socket>;
struct TranClient {
    sockPtr mSock;
    MutBuffer buffer;
    int64_t onlineTime;
    std::string name;
    highClock_t lastRecvTime;
    std::array<char, GBUFFER_SIZE> buf;
};

class Server
{
public:
    explicit Server(asio::io_context& io_context, const std::shared_ptr<spdlog::logger>& logger);
    ~Server();

public:
    bool Run(int32_t port);
    void Stop();

private:
    void Accept();
    void thClientThread(const sockPtr& sockPtr, const std::string& id);
    bool Forward(const sockPtr& sockPtr, FrameBuffer* frame);
    void ReplyRequest(const sockPtr& sockPtr, FrameBuffer* frame);

private:
    template <typename T>
    bool Send(const sockPtr& sockPtr, const T& info, FrameBufferType type, const std::string& fid, const std::string& tid)
    {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive oarchive(ss);
            oarchive(info);
        }
        auto buf = std::make_shared<FrameBuffer>();
        buf->fid = fid;
        buf->tid = tid;
        std::swap(buf->fid, buf->tid);

        buf->data = ss.str().data();
        buf->len = ss.str().size();
        buf->dataType = type;

        return Send(sockPtr, buf.get());
    }
    bool Send(const sockPtr& sockPtr, FrameBuffer* frame);

private:
    bool thRun_{false};
    std::string id_;
    std::thread monitorTh_;
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_;
    std::shared_mutex cliMut_;
    std::shared_ptr<spdlog::logger> logger_;
    std::unordered_map<std::string, std::shared_ptr<TranClient>> clientMap_;
    std::unordered_map<std::string, std::thread> clientThread_;
};

#endif