#include "GUIInterface.h"

#include <spdlog/fmt/bundled/args.h>
#include <spdlog/fmt/bundled/core.h>

#define PARSE_ARGS()                                                           \
    va_list args;                                                              \
    va_start(args, str);                                                       \
    std::string formatStr;                                                     \
    try {                                                                      \
        formatStr = fmt::vformat(str, fmt::make_format_args(args));            \
    } catch (const std::exception& e) {                                        \
        va_end(args);                                                          \
        logPrint_->Error(e.what());                                            \
        return;                                                                \
    }                                                                          \
    va_end(args);                                                              \
    auto qStr = QString::fromStdString(formatStr);

void GUIInterface::Run(const InfoClientVec& vec)
{
}

void GUIInterface::PrintInfo(const char* str, ...)
{
    PARSE_ARGS();
    logPrint_->Info(qStr);
}

void GUIInterface::PrintError(const char* str, ...)
{
    PARSE_ARGS();
    logPrint_->Error(qStr);
}

void GUIInterface::PrintWarn(const char* str, ...)
{
    PARSE_ARGS();
    logPrint_->Warn(qStr);
}

void GUIInterface::PrintDebug(const char* str, ...)
{
    PARSE_ARGS();
    logPrint_->Debug(qStr);
}

void GUIInterface::SetLogControl(LogPrint* logPrint)
{
    logPrint_ = logPrint;
}