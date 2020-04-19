#pragma once
#include "IFactory.h"

class DefaultFactory : public IFactory
{
public:
    IConnectionPointPtr createConnectionPoint(std::string msg) override;
    ILoggerPtr createLogger(std::string msg) override;
    IUserInterfacePtr createUserInterface(std::string msg) override;
};