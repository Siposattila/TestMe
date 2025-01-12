#include "requirement_input.hpp"
#include "input.hpp"
#include <iostream>
#include <memory>
#include <regex>

RequirementInput::RequirementInput(std::string filename) : Input(filename) {}

void RequirementInput::processInput() {

  // Will be used later
  readInput();
}
