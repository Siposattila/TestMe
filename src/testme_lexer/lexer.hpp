#pragma once

#include <cctype>
#include <functional>
#include <string>

enum class TokenType {
  KEYWORD = 0,
  IDENTIFIER = 1,
  OPERATOR = 2,
  NUMBER = 3,
  TYPE = 4,
  SYMBOL = 5,
  STRING = 6,
  END_OF_FILE = 7
};

struct Token {
  TokenType type;
  std::string value;
};

class Lexer {
public:
  explicit Lexer(const std::string &source);

  Token nextToken();

private:
  std::string source;
  size_t position;

  std::string readWhile(std::function<bool(char)> condition);
  std::string readUntil(char stopChar);
  bool valueIsType(const std::string &value);

  void skipWhitespace();
};
