#include "parser.hpp"

Parser::Parser(Lexer &lexer) : lexer(lexer), currentToken(lexer.nextToken()) {}

std::shared_ptr<Class> Parser::parseClass() {
  if (currentToken.type != TokenType::KEYWORD ||
      currentToken.value != "class") {
    throw std::runtime_error("Expected 'class' keyword");
  }
  currentToken = lexer.nextToken();

  if (currentToken.type != TokenType::IDENTIFIER) {
    throw std::runtime_error("Expected class name");
  }
  std::string className = currentToken.value;
  currentToken = lexer.nextToken();

  if (currentToken.value != "{") {
    throw std::runtime_error("Expected '{'");
  }
  currentToken = lexer.nextToken();

  auto clazz = std::make_shared<Class>(className);

  while (currentToken.value != "}") {
    if (currentToken.type == TokenType::KEYWORD &&
        currentToken.value == "void") {
      clazz->addMethod(parseMethod());
    } else if (currentToken.type == TokenType::TYPE) {
      clazz->addVariable(parseVariable());
    }
  }
  currentToken = lexer.nextToken();

  return clazz;
}

std::shared_ptr<Method> Parser::parseMethod() {
  Method method(currentToken.value);
  currentToken = lexer.nextToken();

  if (currentToken.type == TokenType::IDENTIFIER) {
    method.setName(currentToken.value);
    currentToken = lexer.nextToken();
  }

  if (currentToken.value == "(") {
    currentToken = lexer.nextToken();
    while (currentToken.value != ")") {
      method.addVariable(parseVariable());
      if (currentToken.value == ",") {
        currentToken = lexer.nextToken();
      }
    }
    currentToken = lexer.nextToken();
  }

  return std::make_shared<Method>(method);
}

std::shared_ptr<Variable> Parser::parseVariable() {
  if (currentToken.type != TokenType::TYPE) {
    throw std::runtime_error("Expected a variable type");
  }
  std::string type = currentToken.value;
  currentToken = lexer.nextToken();

  if (currentToken.type != TokenType::IDENTIFIER) {
    throw std::runtime_error("Expected variable name");
  }
  std::string name = currentToken.value;
  currentToken = lexer.nextToken();

  return std::make_shared<Variable>(name);
}