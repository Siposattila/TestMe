#include "logger.hpp"

std::unique_ptr<Logger> Logger::mInstance = nullptr;

Logger::Logger(const std::string &filename) {
  mOfFile.open(filename, std::ios::app);
  if (!mOfFile) {
    throw std::ios_base::failure("Failed to open log file");
  }
}

Logger::~Logger() {
  if (mOfFile.is_open()) {
    mOfFile.close();
  }
}

Logger &Logger::getLogger(const std::string &filePath) {
  if (!mInstance) {
    mInstance = std::unique_ptr<Logger>(new Logger(filePath));
  }
  return *mInstance;
}

void Logger::setOutputFile(const std::string &filePath) {
  if (mOfFile.is_open()) {
    mOfFile.close();
  }

  mOfFile.open(filePath, std::ios::app);
  if (!mOfFile) {
    throw std::ios_base::failure("Failed to open new log file");
  }
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
  std::string logMessage = parseLogType(type) + " " + std::to_string(message);

  logToConsole(type, logMessage);
  logToFile(type, logMessage);
}

template <> void Logger::log<float>(LogType type, const float &message) {
  std::string logMessage = parseLogType(type) + " " + std::to_string(message);

  logToConsole(type, logMessage);
  logToFile(type, logMessage);
}

template <> void Logger::log<double>(LogType type, const double &message) {
  std::string logMessage = parseLogType(type) + " " + std::to_string(message);

  logToConsole(type, logMessage);
  logToFile(type, logMessage);
}

template <>
void Logger::log<std::string>(LogType type, const std::string &message) {
  std::string logMessage = parseLogType(type) + " " + message;

  logToConsole(type, logMessage);
  logToFile(type, logMessage);
}

template <> void Logger::log<int>(LogType type, const int &message) {
  std::string logMessage = parseLogType(type) + " " + std::to_string(message);

  logToConsole(type, logMessage);
  logToFile(type, logMessage);
}

void Logger::logToConsole(LogType type, const std::string &message) {
  std::cout << message << std::endl;
}

void Logger::logToFile(LogType type, const std::string &message) {
  if (mOfFile.is_open()) {
    mOfFile << message << std::endl;
  }
}