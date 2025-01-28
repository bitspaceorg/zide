#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <source_location>
#include <sstream>

/* [TODO]
    - Fix template function from being defined in the interface here
    - Add coloring and change format
    - Add logf to do formatted log printing

    - Thread safe implementation
*/

namespace ZD {
struct Logger {
  enum class Level { TRACE, INFO, WARN, ERROR, CRITICAL, DEBUG };

  static std::shared_ptr<Logger> &get();

  void setLogFile(const std::string &filename);
  void setLogLevel(Level level);

  void
  log(Level level,
      const std::source_location location = std::source_location::current(),
      const std::string &message = "");

  template <typename... Args>
  void INFO(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::INFO, location, s.str());
  }

  template <typename... Args>
  void TRACE(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::TRACE, location, s.str());
  }

  template <typename... Args>
  void WARN(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::WARN, location, s.str());
  }

  template <typename... Args>
  void ERROR(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::ERROR, location, s.str());
  }

  template <typename... Args>
  void CRITICAL(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::CRITICAL, location, s.str());
  }

  template <typename... Args>
  void DEBUG(const std::source_location &location, Args &&...args) {
    std::stringstream s;
    ZD::Logger::build_string(location, s, std::forward<Args>(args)...);
    this->log(Level::DEBUG, location, s.str());
  }

  Logger();
  ~Logger();

private:
  std::ofstream m_logFile;
  Level m_logLevel;
  std::mutex m_logMutex;

  std::string m_getTimestamp();
  std::string m_levelToString(Level level);

  template <typename Arg>
  static void build_string(const std::source_location &location,
                           std::stringstream &s, Arg &&arg) {
    s << std::forward<Arg>(arg);
  }

  template <typename Arg, typename... Args>
  static void build_string(const std::source_location &location,
                           std::stringstream &s, Arg &&arg, Args &&...args) {
    s << std::forward<Arg>(arg) << ' ';
    build_string<Args...>(location, s, std::forward<Args>(args)...);
  }
};
} // namespace ZD

#define ZD_INFO(...)                                                           \
  ZD::Logger::get()->INFO(std::source_location::current(), __VA_ARGS__)
#define ZD_TRACE(...)                                                          \
  ZD::Logger::get()->TRACE(std::source_location::current(), __VA_ARGS__)
#define ZD_WARN(...)                                                           \
  ZD::Logger::get()->WARN(std::source_location::current(), __VA_ARGS__)
#define ZD_ERROR(...)                                                          \
  ZD::Logger::get()->ERROR(std::source_location::current(), __VA_ARGS__)
#define ZD_CRITICAL(...)                                                       \
  ZD::Logger::get()->CRITICAL(std::source_location::current(), __VA_ARGS__)
#define ZD_DEBUG(...)                                                          \
  ZD::Logger::get()->DEBUG(std::source_location::current(), __VA_ARGS__)
