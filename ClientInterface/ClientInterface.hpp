#ifndef CLIENTINTERFACE_HPP
#define CLIENTINTERFACE_HPP

#include <spdlog/fmt/bundled/args.h>
#include <spdlog/fmt/bundled/core.h>
#include <string>

#include "InfoClient.hpp"

enum PrintType { PT_DEBUG, PT_WARN, PT_ERROR, PT_INFO };

class ClientUserInterface
{
public:
    ClientUserInterface() = default;
    virtual ~ClientUserInterface() = default;

public:
    template <typename... Args>
    void Info(const std::string& format, Args&&... args)
    {
        Print(PrintType::PT_INFO,
              fmt::format(format, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void Warn(const std::string& format, Args&&... args)
    {
        Print(PrintType::PT_WARN,
              fmt::format(format, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void Error(const std::string& format, Args&&... args)
    {
        Print(PrintType::PT_ERROR,
              fmt::format(format, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void Debug(const std::string& format, Args&&... args)
    {
        Print(PrintType::PT_DEBUG,
              fmt::format(format, std::forward<Args>(args)...));
    }

public:
    virtual void Run(const InfoClientVec& vec) = 0;

protected:
    virtual void Print(PrintType type, const std::string& str) = 0;
};

#endif   // CLIENTINTERFACE_HPP