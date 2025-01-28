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
  void helper(const std::source_location &location, Level level,
              Args &&...args) {
    std::stringstream s;
    ZD::Logger::s_build_string(location, s, std::forward<Args>(args)...);

    log(level, location, s.str());
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
  static void s_build_string(const std::source_location &location,
                             std::stringstream &s, Arg &&arg) {
    s << std::forward<Arg>(arg);
  }

  template <typename Arg, typename... Args>
  static void s_build_string(const std::source_location &location,
                             std::stringstream &s, Arg &&arg, Args &&...args) {
    s << std::forward<Arg>(arg) << ' ';
    s_build_string<Args...>(location, s, std::forward<Args>(args)...);
  }
};
} // namespace ZD

#define ZD_TRACE(...)                                                          \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::TRACE, __VA_ARGS__)
#define ZD_INFO(...)                                                           \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::INFO, __VA_ARGS__)
#define ZD_WARN(...)                                                           \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::WARN, __VA_ARGS__)
#define ZD_ERROR(...)                                                          \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::ERROR, __VA_ARGS__)
#define ZD_CRITICAL(...)                                                       \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::CRITICAL, __VA_ARGS__)
#define ZD_DEBUG(...)                                                          \
  ZD::Logger::get()->helper(std::source_location::current(),                   \
                            ::ZD::Logger::Level::DEBUG, __VA_ARGS__)
