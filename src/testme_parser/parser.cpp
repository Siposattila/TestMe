#include "parser.hpp"
#include <iostream>
#include <testme_meta/class.hpp>
#include <testme_meta/method.hpp>
#include <testme_meta/variable.hpp>

Parser::Parser(Lexer &lexer) : lexer(lexer), currentToken(lexer.nextToken()) {}

// Method: Parser::parseClass
// Parses a class declaration from the token stream.
// Ensures correct syntax and constructs a Class object.
// Returns:
//   - std::shared_ptr<Class>: A pointer to the parsed Class object.
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
    std::cout << "Current Token: " << currentToken.value << std::endl;

    if (currentToken.type == TokenType::KEYWORD &&
        currentToken.value == "void") {
      clazz->addMethod(parseMethod());
    } else if (currentToken.type == TokenType::TYPE) {
      clazz->addVariable(parseVariable());
    } else if (currentToken.value == ";") {
      currentToken = lexer.nextToken();
    } else if (currentToken.value.empty()) {
      currentToken = lexer.nextToken();
    } else {
      throw std::runtime_error("Unexpected token: " + currentToken.value);
    }
  }

  currentToken = lexer.nextToken();
  return clazz;
}

// Method: Parser::parseMethod
// Parses a method definition from the token stream.
// Validates return type, method name, parameter list, and method body syntax.
// Returns:
//   - std::shared_ptr<Method>: A pointer to the parsed Method object.
std::shared_ptr<Method> Parser::parseMethod() {
  std::string returnType = currentToken.value;
  currentToken = lexer.nextToken();

  if (currentToken.type != TokenType::IDENTIFIER) {
    throw std::runtime_error("Expected method name");
  }
  std::string methodName = currentToken.value;
  Method method(methodName);
  currentToken = lexer.nextToken();

  if (currentToken.value != "(") {
    throw std::runtime_error("Expected '(' after method name");
  }
  currentToken = lexer.nextToken();

  while (currentToken.value != ")") {
    if (currentToken.type != TokenType::TYPE) {
      throw std::runtime_error("Expected parameter type");
    }
    std::string paramType = currentToken.value;
    currentToken = lexer.nextToken();

    if (currentToken.type != TokenType::IDENTIFIER) {
      throw std::runtime_error("Expected parameter name");
    }
    std::string paramName = currentToken.value;
    method.addVariable(std::make_shared<Variable>(paramName));

    currentToken = lexer.nextToken();
    if (currentToken.value == ",") {
      currentToken = lexer.nextToken();
    }
  }
  currentToken = lexer.nextToken();

  if (currentToken.value != "{") {
    throw std::runtime_error("Expected '{' for method body");
  }
  currentToken = lexer.nextToken();

  int braceCount = 1;
  while (braceCount > 0 && currentToken.type != TokenType::END_OF_FILE) {
    if (currentToken.value == "{")
      braceCount++;
    if (currentToken.value == "}")
      braceCount--;
    currentToken = lexer.nextToken();
  }

  return std::make_shared<Method>(method);
}

// Method: Parser::parseVariable
// Parses a variable declaration from the token stream.
// Validates the type and name, ensuring a semicolon follows.
// Returns:
//   - std::shared_ptr<Variable>: A pointer to the parsed Variable object.
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
  auto variable = std::make_shared<Variable>(name);
  currentToken = lexer.nextToken();

  if (currentToken.value != ";") {
    throw std::runtime_error("Expected semicolon after variable declaration");
  }
  currentToken = lexer.nextToken();

  return variable;
}