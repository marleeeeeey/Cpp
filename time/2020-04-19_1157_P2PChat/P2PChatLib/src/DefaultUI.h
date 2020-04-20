#pragma once

#include "IUserInterface.h"
#include <queue>
#include <array>
#include <string>
#include "ILogger.h"

class DefaultUI : public IUserInterface
{
    std::queue<std::string> m_inboxMsg;
    ILoggerPtr m_logger;
    ConnectionInfo m_connectionInfo;

public:
    DefaultUI(std::vector<std::string> cmdLines, ILoggerPtr logger);
    std::string getUserInput() override;
    void setInboxMsg(std::string msg) override;
    ConnectionInfo getConnectionInfo() override;
};