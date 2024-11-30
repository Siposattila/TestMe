#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

enum class LogType { INFO, WARNING, ERROR, DEBUG };

class Logger {
public:
  Logger(const std::string &filename);
  ~Logger();

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  static Logger &getLogger(const std::string &filename = "logger.log");

  void setOutputFile(const std::string &filePath);

  template <typename T> void log(LogType logType, const T &message);

  template <> void log<int>(LogType type, const int &message);

  template <> void log<float>(LogType type, const float &message);

  template <> void log<double>(LogType type, const double &message);

  template <> void log<std::string>(LogType type, const std::string &message);

  void logToConsole(LogType type, const std::string &message);
  void logToFile(LogType type, const std::string &message);

private:
  std::string parseLogType(LogType logType) const;

  std::ofstream mOfFile;
  static std::unique_ptr<Logger> mInstance;
};
