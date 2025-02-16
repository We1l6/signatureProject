#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <QDebug>

#define LOG_INFO(...) Logger::getInstance().getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::getInstance().getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().getLogger()->error(__VA_ARGS__)
//#define LOG_DEBUG(...) Logger::getInstance().getLogger()->debug(__VA_ARGS__)

class Logger {
public:
    static Logger& getInstance();
    std::shared_ptr<spdlog::logger> getLogger();
    void setLogLevel(spdlog::level::level_enum level);

private:
    Logger();

    std::shared_ptr<spdlog::logger> logger;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H
