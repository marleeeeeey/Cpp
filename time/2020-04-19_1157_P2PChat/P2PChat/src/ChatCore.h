#pragma once
#include "ChatITF\IConnectionPoint.h"
#include "ChatITF\ILogger.h"
#include "ChatITF\IUserInterface.h"

class ChatCore
{
    IConnectionPointPtr m_connectionPoint;
    IUserInterfacePtr m_userInterface;
    ILoggerPtr m_logger;

    void recieveLoop();
    void sendLoop();

public:
    ChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger);
    ~ChatCore();
    void start();
};