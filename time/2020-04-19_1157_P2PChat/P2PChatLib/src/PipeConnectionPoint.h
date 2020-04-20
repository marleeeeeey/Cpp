#pragma once

#include "IConnectionPoint.h"
#include "ILogger.h"


class PipeConnectionPoint : public IConnectionPoint
{
    struct impl;
    std::unique_ptr<impl> m_pimpl;
    CpStatus m_status;
    ILoggerPtr m_logger;

public:
    PipeConnectionPoint(ILoggerPtr logger);
    ~PipeConnectionPoint();
    void accept(ConnectionInfo connectInfo) override;
    void connect(ConnectionInfo connectInfo) override;
    void send(std::string msg) override;
    std::string receive() override;
    void disconnect() override;
    CpStatus getStatus() override;
};