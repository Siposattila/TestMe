#include "method.hpp"

Method::Method(std::string name) : Meta(name) {}

std::vector<Variable *> Method::getVariables() { return mVariables; }

void Method::addVariable(Variable *variable) { mVariables.push_back(variable); }

void Method::deleteVariable(Variable *variable) {
  auto it = std::remove_if(
      mVariables.begin(), mVariables.end(),
      [variable](Variable *v) { return v->getName() == variable->getName(); });

  if (it != mVariables.end()) {
    mVariables.erase(it, mVariables.end());
  }
}