#pragma once

#include "IConnectionPoint.h"


class SocketConnectionPoint : public IConnectionPoint
{
    struct impl;
    std::unique_ptr<impl> m_pimpl;
    CpStatus m_status;

public:
    SocketConnectionPoint();
    void accept(std::string connectInfo) override;
    void connect(std::string connectInfo) override;
    void send(std::string msg) override;
    std::string receive() override;
    void disconnect() override;
    CpStatus getStatus() override;
};