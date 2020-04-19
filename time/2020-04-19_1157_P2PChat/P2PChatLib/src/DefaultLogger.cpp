#include "DefaultLogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

DefaultLogger::DefaultLogger()
{
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");
    spdlog::set_default_logger(file_logger);
}

void DefaultLogger::LogMsg(std::string msg)
{
    spdlog::info(msg);
}

void DefaultLogger::LogWarning(std::string msg)
{
    spdlog::warn(msg);
}

void DefaultLogger::LogError(std::string msg)
{
    spdlog::error(msg);
}
