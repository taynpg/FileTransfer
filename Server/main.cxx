#include "Server.h"

int main(int argc, char* argv[])
{
    auto logger = CreateLogger("Server", "Server.log");
    asio::io_context io_context;
    Server server(io_context, logger);
    if (!server.Run(9009)) {
        logger->error("Server failed to start.");
        return 1;
    }
    io_context.run();
    return 0;
}