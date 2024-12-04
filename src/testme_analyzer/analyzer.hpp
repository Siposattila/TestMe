#pragma once

#include <cstddef>
#include <string>

class Analyzer {
private:
  size_t difference(const std::string &actual, const std::string &expected);
};
