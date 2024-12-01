#pragma once

#include <cstdint>
#include <fstream>
#include <string>

enum class LogType : uint8_t { INFO, WARNING, ERROR, DEBUG };

class Logger {
public:
  // No copy constructor!
  Logger(const Logger &logger) = delete;

  static Logger &getLogger(const std::string &filename = "testme.log");
  template <typename T> void log(LogType logType, const T &message);

private:
  Logger(const std::string &filename);
  ~Logger();

  const std::string &mFilename;
  std::ofstream mOutputFileStream;
  static Logger *mInstance;

  std::string parseLogType(LogType logType) const;

  void writeToConsole(const std::string &message);
  void writeToFile(const std::string &message);
};
