#pragma once

#include "meta.hpp"
#include "variable.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

class Method : public Meta {
public:
  Method(std::string name);

  std::vector<std::shared_ptr<Variable>> getVariables();
  void addVariable(const std::shared_ptr<Variable> &variable);
  void deleteVariable(const std::shared_ptr<Variable> &variable);

private:
  std::vector<std::shared_ptr<Variable>> mVariables;
};
