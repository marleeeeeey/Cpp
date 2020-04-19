#pragma once

#include "ILogger.h"

class DefaultLogger : public ILogger
{
public:
    DefaultLogger();
    void LogMsg(std::string msg) override;
    void LogWarning(std::string msg) override;
    void LogError(std::string msg) override;
};