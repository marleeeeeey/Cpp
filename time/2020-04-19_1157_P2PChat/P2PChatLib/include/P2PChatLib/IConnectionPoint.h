#pragma once

#include <string>
#include <memory>

class IConnectionPoint
{
public:
    virtual ~IConnectionPoint() = default;
    virtual void accept(std::string param) = 0;
    virtual void connect(std::string param) = 0;
    virtual void send(std::string msg) = 0;
    virtual std::string receive() = 0;
};

using IConnectionPointPtr = std::shared_ptr<IConnectionPoint>;