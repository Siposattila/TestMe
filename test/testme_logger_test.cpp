#include <gtest/gtest.h>
#include <string>
#include <testme_logger/logger.hpp>

std::string getConsoleOutput(std::function<void()> func) {
  std::ostringstream consoleStream;
  std::streambuf *originalBuffer = std::cout.rdbuf();
  std::cout.rdbuf(consoleStream.rdbuf());

  func();

  std::cout.rdbuf(originalBuffer);
  return consoleStream.str();
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageString) {
  Logger &logger = Logger::getLogger();

  std::string testMessage = "This is a test";
  logger.log(LogType::INFO, testMessage);

  std::string expectedMessage = "[INFO] " + testMessage + "\n";
  std::string actualMessage =
      getConsoleOutput([&]() { logger.log(LogType::INFO, testMessage); });

  ASSERT_EQ(actualMessage, expectedMessage);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageInt) {
  Logger &logger = Logger::getLogger();

  int testMessage = 911;
  logger.log(LogType::INFO, testMessage);

  std::string expectedMessage = "[INFO] 911\n";
  std::string actualMessage =
      getConsoleOutput([&]() { logger.log(LogType::INFO, testMessage); });

  ASSERT_EQ(actualMessage, expectedMessage);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageDouble) {
  Logger &logger = Logger::getLogger();

  double testMessage = 911.2;
  logger.log(LogType::INFO, testMessage);

  std::string expectedMessage = "[INFO] 911.200000\n";
  std::string actualMessage =
      getConsoleOutput([&]() { logger.log(LogType::INFO, testMessage); });

  ASSERT_EQ(actualMessage, expectedMessage);
}

TEST(LOGGER_SERVICE_TEST, TestInfoMessageFloat) {
  Logger &logger = Logger::getLogger();

  float testMessage = 2.718f;
  logger.log(LogType::INFO, testMessage);

  std::string expectedMessage = "[INFO] 2.718000\n";
  std::string actualMessage =
      getConsoleOutput([&]() { logger.log(LogType::INFO, testMessage); });

  ASSERT_EQ(actualMessage, expectedMessage);
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
