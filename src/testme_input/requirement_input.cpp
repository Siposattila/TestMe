#include "requirement_input.hpp"
#include "input.hpp"
#include <iostream>
#include <memory>
#include <regex>

RequirementInput::RequirementInput(std::string filename) : Input(filename) {}

void RequirementInput::processInput() {

  // Will be used later
  readInput();
  std::string input = Input::getInput();

  std::regex classRegex(R"(class\s+(\w+)\s*\{)");
  std::regex methodRegex(R"((\w+)\s+(\w+)\s*\(([^)]*)\)\s*\{)");
  std::regex varRegex(R"((\w+)\s+(\w+)\s*;)");

  std::smatch match;

  auto classBegin =
      std::sregex_iterator(input.begin(), input.end(), classRegex);
  auto classEnd = std::sregex_iterator();
  for (std::sregex_iterator i = classBegin; i != classEnd; ++i) {
    Class *newClass = new Class(i->str(1));
    std::cout << "Found class: " << newClass->getName() << std::endl;
  }

  auto methodBegin =
      std::sregex_iterator(input.begin(), input.end(), methodRegex);
  auto methodEnd = std::sregex_iterator();
  for (std::sregex_iterator i = methodBegin; i != methodEnd; ++i) {
    Method *newMethod = new Method(i->str(2));
    std::cout << "Found method: " << newMethod->getName() << std::endl;

    auto varBegin = std::sregex_iterator(input.begin(), input.end(), varRegex);
    auto varEnd = std::sregex_iterator();
    for (std::sregex_iterator j = varBegin; j != varEnd; ++j) {
      Variable *newVariable = new Variable(j->str(2));
      newMethod->addVariable(newVariable);
      std::cout << "Found variable: " << newVariable->getName() << std::endl;
    }
  }
}
