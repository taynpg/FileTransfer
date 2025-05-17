#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <ClientInterface.hpp>

#include "Gui/Control/LogControl.h"

enum class LogType { Info, Warn, Error, Debug };
class GUIInterface : public ClientUserInterface
{
public:
    void Run(const InfoClientVec& vec) override;
    void PrintInfo(const char* str, ...) override;
    void PrintError(const char* str, ...) override;
    void PrintWarn(const char* str, ...) override;
    void PrintDebug(const char* str, ...) override;

public:
    void SetLogControl(LogPrint* logPrint);

private:
    LogPrint* logPrint_;
};

#endif   // GUIINTERFACE_H