#pragma once
#include <string>
#include <memory>
#include <vector>

#include "IConnectionPoint.h"
#include "ILogger.h"
#include "IUserInterface.h"

class IFactory
{
public:
    virtual ~IFactory() = default;
    virtual IConnectionPointPtr createConnectionPoint(std::string msg, ILoggerPtr logger) = 0;
    virtual ILoggerPtr createLogger(std::string msg) = 0;
    virtual IUserInterfacePtr createUserInterface(std::vector<std::string> cmdLines, ILoggerPtr logger) = 0;
};

using IFactoryPtr = std::shared_ptr<IFactory>;
