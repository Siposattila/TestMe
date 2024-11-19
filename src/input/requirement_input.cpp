#include "requirement_input.hpp"
#include "input.hpp"

RequirementInput::RequirementInput(std::string filename) : Input(filename) {}

void RequirementInput::processInput() {
  // TODO: this is not enough will need to process more

  readInput();
}
