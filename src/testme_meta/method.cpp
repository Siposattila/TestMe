#include "method.hpp"

Method::Method(std::string name) : Meta(name) {}

std::vector<std::shared_ptr<Variable>> Method::getVariables() {
  return mVariables;
}

void Method::addVariable(const std::shared_ptr<Variable> &variable) {
  mVariables.push_back(variable);
}

void Method::deleteVariable(const std::shared_ptr<Variable> &variable) {
  auto it = std::remove_if(mVariables.begin(), mVariables.end(),
                           [&variable](const std::shared_ptr<Variable> &v) {
                             return v->getName() == variable->getName();
                           });

  if (it != mVariables.end()) {
    mVariables.erase(it, mVariables.end());
  }
}