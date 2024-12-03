#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

enum class LogType : uint8_t { INFO, WARNING, ERROR, DEBUG };

class Logger {
public:
  ~Logger();

  // No copy constructor!
  Logger(const Logger &logger) = delete;

  static Logger &getLogger(std::string filename = "testme.log");
  template <typename T> void log(LogType logType, const T &message);

private:
  Logger() = default;

  std::ofstream mOutputFileStream;
  static std::unique_ptr<Logger> mInstance;

  std::string parseLogType(LogType logType) const;

  void writeToConsole(std::string message);
  void writeToFile(std::string message);
};
