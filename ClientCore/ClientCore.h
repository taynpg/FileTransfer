#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H

#include <ClientInterface.hpp>
#include <Protocol.h>
#include <asio.hpp>

class ClientCore
{
public:
    ClientCore(asio::io_context& ioContext, const std::shared_ptr<ClientUserInterface>& cf);

public:
    bool Connect(const std::string& ip, int port);
    void Disconnect();

private:
    bool thRun_;
    MutBuffer mutBuffer_;
    asio::ip::tcp::socket socket_;
    asio::io_context ioContext_;

    std::shared_ptr<ClientUserInterface> cf_;
};

#endif   // CLIENT_CORE_H
