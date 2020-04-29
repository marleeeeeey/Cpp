#pragma once
#include "ChatITF\IConnectionPoint.h"
#include "ChatITF\ILogger.h"
#include "ChatITF\IUserInterface.h"

class ClientCore
{
    IConnectionPointPtr m_connectionPoint;
    IUserInterfacePtr m_userInterface;
    ILoggerPtr m_logger;

    void receiveLoop();
    void sendLoop();

public:
    ClientCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger);
    ~ClientCore() = default;
    void start();
};