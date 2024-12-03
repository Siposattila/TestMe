#include "logger.hpp"
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>

std::unique_ptr<Logger> Logger::mInstance = nullptr;

Logger::~Logger() {
  if (mOutputFileStream.is_open()) {
    mOutputFileStream.close();
  }

  mInstance = nullptr;
}

Logger &Logger::getLogger(std::string filename) {
  if (mInstance == nullptr) {
    mInstance.reset(new Logger());
    mInstance.get()->mOutputFileStream =
        std::ofstream(filename, std::ios::out | std::ios::app);
    if (!mInstance.get()->mOutputFileStream.is_open()) {
      throw std::ios_base::failure("Failed to open log file.");
    }
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
  writeToFile(logMessage);
}

void Logger::writeToConsole(std::string message) {
  std::cout << message << std::endl;
}

void Logger::writeToFile(std::string message) {
  mOutputFileStream << message << std::endl;
}

template void Logger::log<int>(LogType type, const int &number);
template void Logger::log<double>(LogType type, const double &number);
template void Logger::log<float>(LogType type, const float &number);
template void Logger::log<std::string>(LogType type,
                                       const std::string &message);
