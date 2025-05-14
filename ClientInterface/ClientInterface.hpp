#ifndef CLIENTINTERFACE_HPP
#define CLIENTINTERFACE_HPP

#include "InfoClient.hpp"

class ClientUserInterface
{
public:
    ClientUserInterface() = default;
    ~ClientUserInterface() = default;

public:
    virtual void Run(const InfoClientVec& vec) = 0;
};

#endif   // CLIENTINTERFACE_HPP