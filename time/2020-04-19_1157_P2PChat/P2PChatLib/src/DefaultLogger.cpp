#include "DefaultLogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

struct DefaultLogger::impl
{
    impl(spdlog::logger in_logger) : logger(in_logger) {}
    spdlog::logger logger;
};

DefaultLogger::DefaultLogger(std::string logFileName)
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    //console_sink->set_level(spdlog::level::warn);
    console_sink->set_level(spdlog::level::trace);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFileName, true);
    file_sink->set_level(spdlog::level::trace);

    auto logger = spdlog::logger("Log", { console_sink, file_sink });
    logger.set_level(spdlog::level::debug);

    m_pimpl = std::make_unique<impl>(logger);
}

void DefaultLogger::LogInfo(std::string msg)
{
    m_pimpl->logger.info(msg);
    m_pimpl->logger.flush();
}

void DefaultLogger::LogWarning(std::string msg)
{
    m_pimpl->logger.warn(msg);
    m_pimpl->logger.flush();
}

void DefaultLogger::LogError(std::string msg)
{
    m_pimpl->logger.error(msg);
    m_pimpl->logger.flush();
}
