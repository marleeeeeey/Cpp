#pragma once

#include "ChatITF\ILogger.h"
#include "ChatITF\IUserInterface.h"

class ServerCore
{
    struct impl;
    std::unique_ptr<impl> m_pimpl;

public:
    ServerCore(IUserInterfacePtr ui, ILoggerPtr logger);
    ~ServerCore();
    void start();    
};