#include "testme_logger/logger.hpp"

int main() {
  std::string log = "testme.log";
  Logger::getLogger(log).log(LogType::INFO, std::string("Anyuka!"));

  return 0;
}
