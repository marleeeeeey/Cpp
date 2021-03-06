#pragma once

#include <string>
#include <memory>
#include "ConnectionInfo.hpp"

enum class CpStatus
{
    ConnectionError,
    Connected,
    Disconnected,
};

class IConnectionPoint
{
public:
    virtual ~IConnectionPoint() = default;
    virtual void accept(ConnectionInfo connectInfo) = 0;
    virtual void connect(ConnectionInfo connectInfo) = 0;
    virtual void send(std::string msg) = 0;
    virtual void disconnect() = 0;
    virtual std::string receive() = 0;
    virtual CpStatus getStatus() = 0;

};

using IConnectionPointPtr = std::shared_ptr<IConnectionPoint>;