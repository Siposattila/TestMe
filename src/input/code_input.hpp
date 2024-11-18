#pragma once

#include "input.hpp"
#include <string>

class CodeInput : public Input {
public:
  CodeInput(std::string filename);

  void processInput() override;
};
