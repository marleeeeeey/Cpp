#pragma once

#include "IConnectionPoint.h"

class SocketConnectionPoint : public IConnectionPoint
{
public:
    void accept(std::string param) override;
    void connect(std::string param) override;
    void send(std::string msg) override;
    std::string receive() override;
};