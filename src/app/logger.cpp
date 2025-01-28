#include "logger.h"

ZD::Logger::Logger() : m_logLevel(Level::TRACE) {}

ZD::Logger::~Logger() {
  if (m_logFile.is_open())
    m_logFile.close();
}

std::shared_ptr<ZD::Logger> &ZD::Logger::get() {
  static std::shared_ptr<ZD::Logger> logger(new ZD::Logger());
  return logger;
}

void ZD::Logger::setLogFile(const std::string &filename) {
  // [TODO] Add lock here to make this thread safe
  if (m_logFile.is_open()) {
    m_logFile.close();
  }

  m_logFile.open(filename, std::ios::out | std::ios::app);

  if (!m_logFile) {
    std::cerr << "Logger: Unable to open log file: " << filename << std::endl;
  }
}

void ZD::Logger::setLogLevel(Level level) {
  // [TODO] Add lock here to make this thread safe
  this->m_logLevel = level;
}

void ZD::Logger::log(Level level, const std::source_location location,
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
    m_logFile << entry.str() << std::endl;
  } else {
    std::cerr << entry.str() << std::endl;
  }
}

/*template <typename... Args>*/
/*void ZD::Logger::logf(Level level, const std::string &format,*/
/*                      const std::source_location location, Args... args) {*/
/*  // [TODO] Add lock here to make this thread safe*/
/*  if (level < m_logLevel)*/
/*    return;*/
/**/
/*  std::ostringstream oss;*/
/*  size_t pos = 0;*/
/*  const size_t n = sizeof...(args);*/
/*  size_t i = 0;*/
/**/
/*  ((oss << format.substr(pos, (pos = format.find_first_of('%', pos)) - i++)*/
/*        << args,*/
/*    pos++),*/
/*   ...);*/
/**/
/*  oss << " file: " << location.file_name() << "(" << location.line() << ":"*/
/*      << location.column() << ") `" << location.function_name() << "`: ";*/
/**/
/*  log(level, std::source_location::current(), oss.str());*/
/*}*/

std::string ZD::Logger::m_levelToString(Level level) {
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

std::string ZD::Logger::m_getTimestamp() {
  std::time_t now = std::time(nullptr);
  char buffer[20];
  std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S",
                std::localtime(&now));
  return buffer;
}
