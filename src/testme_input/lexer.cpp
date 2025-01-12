#include "lexer.hpp"

Lexer::Lexer(const std::string &source) : source(source), position(0) {}

Token Lexer::nextToken() {
  while (position < source.length() && std::isspace(source[position])) {
    ++position;
  }

  if (position >= source.length()) {
    return {TokenType::END_OF_FILE, ""};
  }

  char currentChar = source[position];

  if (std::isalpha(currentChar) || currentChar == '_') {
    std::string value =
        readWhile([](char c) { return std::isalnum(c) || c == '_'; });
    if (value == "class" || value == "void" || value == "int" ||
        value == "string") {
      return {TokenType::KEYWORD, value};
    }
    return {TokenType::IDENTIFIER, value};
  }

  if (std::isdigit(currentChar)) {
    std::string value = readWhile([](char c) { return std::isdigit(c); });
    return {TokenType::NUMBER, value};
  }

  if (std::isalpha(currentChar)) {
    std::string value = readWhile([](char c) { return std::isalpha(c); });
    if (valueIsType(value)) {
      return {TokenType::TYPE, value};
    }
  }

  if (currentChar == '=' || currentChar == '+' || currentChar == '-' ||
      currentChar == '{' || currentChar == '}') {
    std::string value(1, currentChar);
    ++position;
    return {TokenType::OPERATOR, value};
  }

  if (currentChar == '"') {
    ++position;
    std::string value = readUntil('"');
    ++position;
    return {TokenType::STRING, value};
  }

  ++position;
  return {TokenType::SYMBOL, std::string(1, currentChar)};
}

std::string Lexer::readWhile(std::function<bool(char)> condition) {
  std::string result;
  while (position < source.length() && condition(source[position])) {
    result += source[position];
    ++position;
  }
  return result;
}

std::string Lexer::readUntil(char stopChar) {
  std::string result;
  while (position < source.length() && source[position] != stopChar) {
    result += source[position];
    ++position;
  }
  return result;
}

bool Lexer::valueIsType(const std::string &value) {
  return value == "int" || value == "string" || value == "void";
}
