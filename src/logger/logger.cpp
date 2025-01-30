#include "logger.h"

Logger::Logger() {
    try {
        logger = spdlog::basic_logger_mt("file_logger", "logs/logs.log", true);
        logger->set_level(spdlog::level::info);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
        logger->info("Logger initialized.");
    } catch (const spdlog::spdlog_ex& ex) {
        qWarning() << "Logger initialization failed: " << ex.what();
    }
}
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    return logger;
}

void Logger::setLogLevel(spdlog::level::level_enum level) {
    logger->set_level(level);
}
