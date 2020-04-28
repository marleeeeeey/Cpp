#pragma once

#include "ChatITF\IConnectionPoint.h"
#include "ChatITF\ILogger.h"

class SocketConnectionPoint : public IConnectionPoint
{
    struct impl;
    std::unique_ptr<impl> m_pimpl;
    CpStatus m_status;
    ILoggerPtr m_logger;

public:
    SocketConnectionPoint(ILoggerPtr logger);
    ~SocketConnectionPoint();
    void accept(ConnectionInfo connectInfo) override;
    void connect(ConnectionInfo connectInfo) override;
    void send(std::string msg) override;
    std::string receive() override;
    void disconnect() override;
    CpStatus getStatus() override;
};