#include <filesystem>
#include <format>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <testme_logger/logger.hpp>

TEST(LOGGER_SERVICE_TEST, TestInfoMessageStringIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  std::string message = "This is a test";
  Logger::getLogger().log(LogType::INFO, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = "[INFO] " + message + "\n";

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageIntIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  int message = 911;
  Logger::getLogger().log(LogType::INFO, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = std::format("[INFO] {}\n", message);

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageDoubleIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  double message = 911.2;
  Logger::getLogger().log(LogType::INFO, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = std::format("[INFO] {}\n", message);

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageFloatIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  float message = 2.718f;
  Logger::getLogger().log(LogType::INFO, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = std::format("[INFO] {}\n", message);

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestErrorMessageFloatIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  float message = 2.718f;
  Logger::getLogger().log(LogType::ERROR, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = std::format("[ERROR] {}\n", message);

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestDebugMessageIntIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  int message = 911;
  Logger::getLogger().log(LogType::DEBUG, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = std::format("[DEBUG] {}\n", message);

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestWarningMessageStringIsCorrectCout) {
  std::stringstream buffer;
  std::streambuf *coutBuf = std::cout.rdbuf(buffer.rdbuf());

  std::string message = "This is a test";
  Logger::getLogger().log(LogType::WARNING, message);

  std::string actualMessage = buffer.str();
  std::string expectedMessage = "[WARNING] " + message + "\n";

  ASSERT_EQ(actualMessage, expectedMessage);

  std::cout.rdbuf(coutBuf);
}

TEST(LOGGER_SERVICE_TEST, TestWarningMessageStringIsCorrectFile) {
  // Make it so we can create a new file
  Logger::getLogger().~Logger();

  std::string filename = "unittest.log";
  std::vector<std::string> fileLines;

  std::string message = "This is a test";
  Logger::getLogger(filename).log(LogType::WARNING, message);

  std::ifstream file(filename);
  if (!file.is_open()) {
    FAIL() << "Failed to open file: " << filename;
  }

  std::string line;
  while (std::getline(file, line)) {
    fileLines.push_back(line);
  }
  file.close();

  try {
    if (std::filesystem::remove(filename)) {
      std::cout << "File deleted successfully.\n";
    } else {
      FAIL() << "File not found: " << filename;
    }
  } catch (const std::filesystem::filesystem_error &e) {
    FAIL() << "Error: " << e.what() << '\n';
  }

  std::string actualMessage = fileLines.front();
  std::string expectedMessage = "[WARNING] " + message;

  ASSERT_EQ(actualMessage, expectedMessage);
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
