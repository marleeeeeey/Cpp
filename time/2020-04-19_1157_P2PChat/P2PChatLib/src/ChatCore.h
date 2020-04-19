#pragma once
#include "IConnectionPoint.h"
#include "ILogger.h"
#include "IUserInterface.h"

class ChatCore
{
    IConnectionPointPtr m_connectionPoint;
    IUserInterfacePtr m_userInterface;
    ILoggerPtr m_logger;

public:
    ChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger);
    ~ChatCore();
    void start();
};