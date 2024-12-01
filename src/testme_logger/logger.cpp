#include "logger.hpp"
#include <format>
#include <fstream>
#include <iostream>

Logger *Logger::mInstance = nullptr;

Logger::Logger(const std::string &filename) : mFilename(filename) {}

Logger::~Logger() {
  if (mOutputFileStream.is_open()) {
    mOutputFileStream.close();
  }
}

Logger &Logger::getLogger(const std::string &filename) {
  if (mInstance != nullptr) {
    mInstance = new Logger(filename);
  }

  return *mInstance;
}

std::string Logger::parseLogType(LogType logType) const {
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

template <typename T> void Logger::log(LogType type, const T &message) {
  std::string logMessage = std::format("{} {}", parseLogType(type), message);
  writeToConsole(logMessage);
  // writeToFile(logMessage);
}

void Logger::writeToConsole(const std::string &message) {
  std::cout << message << std::endl;
}

// FIXME: segfault static maybe????
void Logger::writeToFile(const std::string &message) {
  // if (!mOutputFileStream.is_open()) {
  std::cout << mFilename << std::endl;
  // mOutputFileStream.open(mFilename, std::ios::out | std::ios::app);
  //  if (!mOutputFileStream.is_open()) {
  //    throw std::ios_base::failure("Failed to open log file.");
  //  }
  // }
  //  mOutputFileStream << message << std::endl;
  //  mOutputFileStream.flush();
}

template void Logger::log<int>(LogType type, const int &number);
template void Logger::log<double>(LogType type, const double &number);
template void Logger::log<float>(LogType type, const float &number);
template void Logger::log<std::string>(LogType type,
                                       const std::string &message);
