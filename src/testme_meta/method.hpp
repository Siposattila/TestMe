#pragma once

#include "meta.hpp"
#include "variable.hpp"
#include <string>
#include <vector>

class Method : public Meta {
public:
  Method(std::string name);

  std::vector<Variable *> getVariables();
  void addVariable(Variable *variable);
  void deleteVariable(Variable *variable);

private:
  std::vector<Variable *> mVariables;
};
