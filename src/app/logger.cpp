#include "logger.h"

namespace ZD {
Logger::Logger() : m_logLevel(Level::TRACE) {}

Logger::~Logger() {
  if (m_logFile.is_open())
    m_logFile.close();
}

std::shared_ptr<Logger> &Logger::get() {
  static std::shared_ptr<Logger> logger(new Logger());
  return logger;
}

void Logger::setLogFile(const std::string &filename) {
  // [TODO] Add lock here to make this thread safe
  if (m_logFile.is_open()) {
    m_logFile.close();
  }

  m_logFile.open(filename, std::ios::out | std::ios::app);

  if (!m_logFile) {
    std::cerr << "Logger: Unable to open log file: " << filename << std::endl;
  }
}

void Logger::setLogLevel(Level level) {
  // [TODO] Add lock here to make this thread safe
  this->m_logLevel = level;
}

void Logger::log(Level level, const std::source_location location,
                 const std::string &message) {
  // [TODO] Add lock here to make this thread safe
  if (level < this->m_logLevel)
    return;

  std::ostringstream entry;
  entry << "[" << this->m_getTimestamp() << "] "
        << "[" << this->m_levelToString(level) << "] "
        << "file: " << location.file_name() << '(' << location.line() << ':'
        << location.column() << ") `" << location.function_name()
        << "`: " << message;

  if (m_logFile.is_open()) {
    m_logFile << entry.str();
  } else {
    std::cerr << entry.str() << std::endl;
  }
}

std::string Logger::m_levelToString(Level level) {
  switch (level) {
  case Level::TRACE:
    return "TRACE";
  case Level::INFO:
    return "INFO";
  case Level::WARN:
    return "WARN";
  case Level::ERROR:
    return "ERROR";
  case Level::CRITICAL:
    return "CRITICAL";
  case Level::DEBUG:
    return "DEBUG";
  default:
    return "LOG";
  }
}

std::string Logger::m_getTimestamp() {
  std::time_t now = std::time(nullptr);
  char buffer[20];
  std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S",
                std::localtime(&now));
  return buffer;
}
} // namespace ZD
