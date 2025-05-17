#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <ClientInterface.hpp>
#include <string>

#include "Gui/Control/LogControl.h"

enum class LogType { Info, Warn, Error, Debug };
class GUIInterface : public ClientUserInterface
{
public:
    void Run(const InfoClientVec& vec) override;
    void Print(PrintType type, const std::string& str) override;

public:
    void SetLogControl(LogPrint* logPrint);
    std::string now_str();

private:
    LogPrint* logPrint_;
};

#endif   // GUIINTERFACE_H