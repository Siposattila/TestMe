#include "class.hpp"

Class::Class(const std::string &name) : Meta(name) {}

std::vector<std::shared_ptr<Variable>> Class::getVariables() {
  return mVariables;
}

void Class::addVariable(const std::shared_ptr<Variable> &variable) {
  mVariables.push_back(variable);
}

void Class::deleteVariable(const std::shared_ptr<Variable> &variable) {
  auto it = std::remove(mVariables.begin(), mVariables.end(), variable);
  mVariables.erase(it, mVariables.end());
}

std::vector<std::shared_ptr<Method>> Class::getMethods() { return mMethods; }

void Class::addMethod(const std::shared_ptr<Method> &method) {
  mMethods.push_back(method);
}

void Class::deleteMethod(const std::shared_ptr<Method> &method) {
  auto it = std::remove(mMethods.begin(), mMethods.end(), method);
  mMethods.erase(it, mMethods.end());
}