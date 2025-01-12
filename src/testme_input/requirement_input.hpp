#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "../testme_meta/class.hpp"
#include "../testme_meta/method.hpp"
#include "../testme_meta/variable.hpp"
#include "input.hpp"

class RequirementInput : public Input {
public:
  RequirementInput(std::string filename);

  void processInput() override;
};
