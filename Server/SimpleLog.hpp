#ifndef SIMPLELOG_HPP
#define SIMPLELOG_HPP

#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define LOG_BUFFSIZE (1024 * 100)
inline std::shared_ptr<spdlog::logger> CreateLogger(const std::string& loggerName, const std::string& logPath)
{
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logPath, LOG_BUFFSIZE, 3);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l]: %v");
    console_sink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%l]: %v%$");
    std::vector<spdlog::sink_ptr> sinks{file_sink, console_sink};
    auto logger = std::make_shared<spdlog::logger>(loggerName, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::debug);
    spdlog::register_logger(logger);
    return logger;
}

#endif