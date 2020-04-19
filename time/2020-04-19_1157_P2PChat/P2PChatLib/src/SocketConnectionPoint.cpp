#include "SocketConnectionPoint.h"

void SocketConnectionPoint::accept(std::string connectInfo)
{
}

void SocketConnectionPoint::connect(std::string connectInfo)
{
}

void SocketConnectionPoint::send(std::string msg)
{
}

std::string SocketConnectionPoint::receive()
{
    return "Dummy recieved data";
}

void SocketConnectionPoint::disconnect()
{
}

CpStatus SocketConnectionPoint::getStatus()
{
    return CpStatus::Connected;
}
