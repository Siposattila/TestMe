#pragma once

#include "meta.hpp"
#include "method.hpp"
#include "variable.hpp"
#include <string>
#include <vector>

class Class : public Meta {
public:
  Class(std::string name);

  std::vector<Variable *> getVariables();
  void addVariable(Variable *variable);
  void deleteVariable(Variable *variable);

  std::vector<Method *> getMethods();
  void addMethod(Method *method);
  void deleteMethod(Method *method);

private:
  std::string mName;
  std::vector<Variable *> mVariables;
  std::vector<Method *> mMethods;
};
