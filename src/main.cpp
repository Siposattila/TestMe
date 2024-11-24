#include <iostream>
#include <testme_input/code_input.hpp>

int main() {
  CodeInput input("data/input/example.cs");
  input.processInput();
  std::cout << input.getTreeString() << std::endl;

  return 0;
}
