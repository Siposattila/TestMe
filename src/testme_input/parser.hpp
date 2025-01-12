#pragma once
#include "../testme_meta/class.hpp"
#include "../testme_meta/method.hpp"
#include "../testme_meta/variable.hpp"
#include "lexer.hpp"
#include <memory>
#include <stdexcept>
#include <vector>

class Parser {
public:
  explicit Parser(Lexer &lexer);

  std::shared_ptr<Class> parseClass();

private:
  Lexer &lexer;
  Token currentToken;

  std::shared_ptr<Method> parseMethod();
  std::shared_ptr<Variable> parseVariable();
};