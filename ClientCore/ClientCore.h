#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H

#include <ClientInterface.hpp>
#include <Protocol.h>
#include <asio.hpp>
#include <array>

class ClientCore : public std::enable_shared_from_this<ClientCore>
{
public:
    ClientCore(asio::io_context& ioContext, const std::shared_ptr<ClientUserInterface>& cf);

public:
    bool Connect(const std::string& ip, int port);
    void Disconnect();

private:
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
