#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H

#include <ClientInterface.hpp>
#include <globalDefine.h>
#include <Protocol.h>
#include <array>
#include <asio.hpp>

class ClientCore : public std::enable_shared_from_this<ClientCore>
{
public:
    ClientCore(asio::io_context& ioContext);

public:
    void SetUserInterface(const std::shared_ptr<ClientUserInterface>& cf);
    bool Connect(const std::string& ip, int port);
    void Disconnect();

private:
    template <typename T>
    bool Send(const T& info, FrameBufferType type, const std::string& fid,
              const std::string& tid)
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

        auto ssData = ss.str();
        buf->len = ssData.size();
        buf->data = ssData.data();
        buf->dataType = type;
        return Send(buf.get());
    }
    bool Send(FrameBuffer* frame);
    bool Send(const char* data, int len);
    void Recv();
    void UseFrame(FrameBuffer* frame);

private:
    bool thRun_;
    MutBuffer mutBuffer_;
    asio::ip::tcp::socket socket_;
    asio::io_context ioContext_;
    std::array<char, 1024> recvBuffer_;
    std::shared_ptr<ClientUserInterface> cf_;
};

#endif   // CLIENT_CORE_H
