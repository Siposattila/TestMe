#include <gtest/gtest.h>
#include <string>
#include <testme_logger/logger.hpp>

TEST(LOGGER_SERVICE_TEST, TestInfoMessage) {
  std::stringstream outputStream;
  // Logger logger;

  // std::ostream *oldStream = logger.outputStream;
  // logger.outputStream = &outputStream;

  // Logger::Logger()::log(LogType::INFO, "This is an info message");

  // logger.outputStream = oldStream;

  std::string expectedOutput = "[INFO] This is an info message\n";
  ASSERT_EQ(outputStream.str(), expectedOutput);
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
