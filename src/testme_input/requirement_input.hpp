#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "input.hpp"

class RequirementInput : public Input {
public:
  RequirementInput(std::string filename);

  void processInput() override;
};
