#ifndef CLIENTINTERFACE_HPP
#define CLIENTINTERFACE_HPP

#include <string>

#include "InfoClient.hpp"

class ClientUserInterface
{
public:
    ClientUserInterface() = default;
    ~ClientUserInterface() = default;

public:
    virtual void Run(const InfoClientVec& vec) = 0;
    virtual void Print(const std::string& str, ...) = 0;
};

#endif   // CLIENTINTERFACE_HPP