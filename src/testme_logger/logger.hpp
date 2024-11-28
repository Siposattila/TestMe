#pragma once

#include <fstream>
#include <iostream>
#include <string>

enum class LogType { INFO, WARNING, ERROR, DEBUG };

class Logger {
public:
  void setOutputFile(const std::string &filePath);

  void log(LogType logType, const std::string &message);

  void setOutputStream(std::ostream &outputStream);

private:
  Logger();

  // FIXME: This is not needed do not include please
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  std::string parseLogType(LogType logType);

  std::ostream *mOutputStream;
  std::ofstream mFileStream;
};
