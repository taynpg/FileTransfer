#include "GUIInterface.h"

#include <spdlog/fmt/bundled/args.h>
#include <spdlog/fmt/bundled/core.h>

void GUIInterface::SetLogControl(LogPrint* logPrint)
{
    logPrint_ = logPrint;
}

void GUIInterface::Run(const InfoClientVec& vec)
{
}

void GUIInterface::Print(PrintType type, const std::string& str)
{
    auto qstr = QString::fromStdString(str);
    switch (type) {
    case PT_DEBUG:
        logPrint_->Debug(qstr);
        break;
    case PT_INFO:
        logPrint_->Info(qstr);
        break;
    case PT_WARN:
        logPrint_->Warn(qstr);
        break;
    case PT_ERROR:
        logPrint_->Error(qstr);
        break;
    default:
        break;
    }
}
