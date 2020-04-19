#pragma once
#include "IFactory.h"

class DefaultFactory : public IFactory
{
public:
    IConnectionPointPtr createConnectionPoint(std::string msg, ILoggerPtr logger) override;
    ILoggerPtr createLogger(std::string msg) override;
    IUserInterfacePtr createUserInterface(std::string msg, ILoggerPtr logger) override;
};