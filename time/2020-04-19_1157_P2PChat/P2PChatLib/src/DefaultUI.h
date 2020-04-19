#pragma once

#include "IUserInterface.h"
#include <queue>
#include "ILogger.h"

class DefaultUI : public IUserInterface
{
    std::queue<std::string> m_inboxMsg;
    ILoggerPtr m_logger;

public:
    DefaultUI(ILoggerPtr logger);
    std::string getUserInput() override;
    void setInboxMsg(std::string msg) override;
};