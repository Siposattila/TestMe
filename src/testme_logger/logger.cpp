#include "logger.hpp"

Logger::Logger() : mOutputStream(&std::cout) {}

void Logger::setOutputFile(const std::string &filePath) {
  if (mFileStream.is_open()) {
    mFileStream.close();
  }

  mFileStream.open(filePath, std::ios::out | std::ios::app);
  if (mFileStream.is_open()) {
    mOutputStream = &mFileStream;
  } else {
    mOutputStream = &std::cout;
  }
}

void Logger::log(LogType logType, const std::string &message) {
  *mOutputStream << parseLogType(logType) << message << std::endl;
}

std::string Logger::parseLogType(LogType logType) {
  switch (logType) {
  case LogType::INFO:
    return "[INFO]";
  case LogType::WARNING:
    return "[WARNING]";
  case LogType::ERROR:
    return "[ERROR]";
  case LogType::DEBUG:
    return "[DEBUG]";
  }
}

// for testing
void Logger::setOutputStream(std::ostream &outputStream) {
  mOutputStream = &outputStream;
}
