#include "ClientCore.h"

ClientCore::ClientCore(asio::io_context& ioContext, const std::shared_ptr<ClientUserInterface>& cf)
    : socket_(ioContext), cf_(cf)
{
}

bool ClientCore::Connect(const std::string& ip, int port)
{
    try {
        asio::ip::tcp::resolver resolver(ioContext_);
        auto ep = resolver.resolve(ip, std::to_string(port));
        asio::connect(socket_, ep);
        cf_->Print("Connected to server {}:{} success.", ip, port);
        return true;
    } catch (const std::exception& ex) {
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
