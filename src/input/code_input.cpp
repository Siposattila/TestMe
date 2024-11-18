#include "code_input.hpp"
#include "input.hpp"

CodeInput::CodeInput(std::string filename) : Input(filename) {}

void CodeInput::processInput() {
  // TODO: this is not enough will need to identify the language and use the
  // correct grammar

  readInput();
}
