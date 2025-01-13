#pragma once

#include <memory>
#include <testme_lexer/lexer.hpp>
#include <testme_meta/class.hpp>
#include <testme_meta/method.hpp>
#include <testme_meta/variable.hpp>

class Parser {
public:
  Parser(Lexer &lexer);

  std::shared_ptr<Class> parseClass();

private:
  Lexer &lexer;
  Token currentToken;

  std::shared_ptr<Method> parseMethod();
  std::shared_ptr<Variable> parseVariable();
};
