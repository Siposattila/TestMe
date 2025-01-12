#pragma once

#include "meta.hpp"
#include "method.hpp"
#include "variable.hpp"
#include <memory>
#include <string>
#include <vector>

class Class : public Meta {
public:
  explicit Class(const std::string &name);

  std::vector<std::shared_ptr<Variable>> getVariables();
  void addVariable(const std::shared_ptr<Variable> &variable);
  void deleteVariable(const std::shared_ptr<Variable> &variable);

  std::vector<std::shared_ptr<Method>> getMethods();
  void addMethod(const std::shared_ptr<Method> &method);
  void deleteMethod(const std::shared_ptr<Method> &method);

private:
  std::string mName;
  std::vector<std::shared_ptr<Variable>> mVariables;
  std::vector<std::shared_ptr<Method>> mMethods;
};
