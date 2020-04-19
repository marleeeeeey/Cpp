#pragma once

#include "IConnectionPoint.h"

class SocketConnectionPoint : public IConnectionPoint
{
public:
    void accept(std::string connectInfo) override;
    void connect(std::string connectInfo) override;
    void send(std::string msg) override;
    std::string receive() override;
    void disconnect() override;
    CpStatus getStatus() override;
};