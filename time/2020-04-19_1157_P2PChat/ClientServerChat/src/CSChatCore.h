#pragma once

#include "ChatITF\IConnectionPoint.h"
#include "ChatITF\ILogger.h"
#include "ChatITF\IUserInterface.h"

class CSChatCore
{
    IConnectionPointPtr m_connectionPoint;
    IUserInterfacePtr m_userInterface;
    ILoggerPtr m_logger;

public:
    CSChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger);
    ~CSChatCore();
    void start();    
};