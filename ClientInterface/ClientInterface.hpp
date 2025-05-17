#ifndef CLIENTINTERFACE_HPP
#define CLIENTINTERFACE_HPP

#include "InfoClient.hpp"

class ClientUserInterface
{
public:
    ClientUserInterface() = default;
    virtual ~ClientUserInterface() = default;

public:
    virtual void Run(const InfoClientVec& vec) = 0;
    virtual void PrintInfo(const char* str, ...) = 0;
    virtual void PrintError(const char* str, ...) = 0;
    virtual void PrintWarn(const char* str, ...) = 0;
    virtual void PrintDebug(const char* str, ...) = 0;
};

#endif   // CLIENTINTERFACE_HPP