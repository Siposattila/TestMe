#pragma once
#include "class.hpp"
#include "lexer.hpp"
#include "method.hpp"
#include "variable.hpp"
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