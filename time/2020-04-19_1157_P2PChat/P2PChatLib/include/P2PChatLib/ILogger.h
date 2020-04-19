#pragma once

#include <string>
#include <memory>

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void LogMsg(std::string msg) = 0;
    virtual void LogWarning(std::string msg) = 0;
    virtual void LogError(std::string msg) = 0;
};

using ILoggerPtr = std::shared_ptr<ILogger>;