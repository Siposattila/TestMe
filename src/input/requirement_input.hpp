#pragma once

#include "input.hpp"

class RequirementInput : public Input {
public:
  RequirementInput(std::string filename);

  void processInput() override;
};
