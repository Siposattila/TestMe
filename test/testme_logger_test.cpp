#include <format>
#include <gtest/gtest.h>
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

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
