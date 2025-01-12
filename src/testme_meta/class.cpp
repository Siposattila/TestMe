#include "class.hpp"

Class::Class(std::string name) : Meta(name) {}

std::vector<Variable *> Class::getVariables() { return mVariables; }

void Class::addVariable(Variable *variable) { mVariables.push_back(variable); }

void Class::deleteVariable(Variable *variable) {
  auto it = std::remove(mVariables.begin(), mVariables.end(), variable);
  mVariables.erase(it, mVariables.end());
}

std::vector<Method *> Class::getMethods() { return mMethods; }

void Class::addMethod(Method *method) { mMethods.push_back(method); }

void Class::deleteMethod(Method *method) {
  auto it = std::remove(mMethods.begin(), mMethods.end(), method);
  mMethods.erase(it, mMethods.end());
}