#pragma once
#include <cctype>
#include <functional>
#include <string>
#include <vector>

enum class TokenType {
  KEYWORD,
  IDENTIFIER,
  OPERATOR,
  NUMBER,
  TYPE,
  SYMBOL,
  STRING,
  END_OF_FILE
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
};
