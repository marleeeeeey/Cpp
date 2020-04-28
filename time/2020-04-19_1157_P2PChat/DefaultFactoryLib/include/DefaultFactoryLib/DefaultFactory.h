#pragma once
#include "ChatITF\IFactory.h"

class DefaultFactory : public IFactory
{
public:
    IConnectionPointPtr createConnectionPoint(std::string msg, ILoggerPtr logger) override;
    ILoggerPtr createLogger(std::string logFilePath) override;
    IUserInterfacePtr createUserInterface(std::vector<std::string> cmdLines, ILoggerPtr logger) override;
};