#include "lexer.hpp"

Lexer::Lexer(const std::string &source) : source(source), position(0) {}

// Method: Lexer::nextToken
// Retrieves the next token from the source code.
// Processes whitespace, identifiers, keywords, numbers, symbols, and operators.
// Returns:
//   - Token: The next token with its type and value.
Token Lexer::nextToken() {
  while (position < source.length() && std::isspace(source[position])) {
    ++position;
  }

  if (position >= source.length()) {
    return {TokenType::END_OF_FILE, ""};
  }

  char currentChar = source[position];

  // Check if the current character is the start of an identifier (letter or
  // underscore).
  if (std::isalpha(currentChar) || currentChar == '_') {
    // Read all characters that form an identifier (letters, digits,
    // underscores).
    std::string value =
        readWhile([](char c) { return std::isalnum(c) || c == '_'; });

    if (valueIsType(value)) {
      return {TokenType::TYPE, value};
    }

    if (value == "class" || value == "void") {
      return {TokenType::KEYWORD, value};
    }

    return {TokenType::IDENTIFIER, value};
  }

  if (std::isdigit(currentChar)) {
    std::string value = readWhile([](char c) { return std::isdigit(c); });
    return {TokenType::NUMBER, value};
  }

  if (currentChar == '{') {
    ++position;
    return {TokenType::SYMBOL, "{"};
  }

  if (currentChar == '}') {
    ++position;
    return {TokenType::SYMBOL, "}"};
  }

  if (currentChar == ';') {
    ++position;
    return {TokenType::SYMBOL, ";"};
  }

  if (currentChar == '=' || currentChar == '+' || currentChar == '-') {
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

// Method: Lexer::readWhile
// Reads characters from the source as long as the provided condition is true.
// Parameters:
//   - condition: A function defining the condition for reading characters.
// Returns:
//   - std::string: The collected characters that satisfy the condition.
std::string Lexer::readWhile(std::function<bool(char)> condition) {
  std::string result;
  while (position < source.length() && condition(source[position])) {
    result += source[position];
    ++position;
  }
  return result;
}

// Method: Lexer::readUntil
// Reads characters from the source until the specified stop character is
// encountered. Parameters:
//   - stopChar: The character to stop reading at.
// Returns:
//   - std::string: The collected characters before the stop character.
std::string Lexer::readUntil(char stopChar) {
  std::string result;
  while (position < source.length() && source[position] != stopChar) {
    result += source[position];
    ++position;
  }
  return result;
}

// Method: Lexer::valueIsType
// Checks if the given string matches a known type keyword (e.g., "int",
// "string"). Parameters:
//   - value: The string to check.
// Returns:
//   - bool: True if the value is a recognized type, false otherwise.
bool Lexer::valueIsType(const std::string &value) {
  return value == "int" || value == "string";
}

// Method: Lexer::skipWhitespace
// Skips all whitespace characters in the source code.
// Advances the position until a non-whitespace character is found or the end of
// the source is reached. No return value.
void Lexer::skipWhitespace() {
  while (position < source.length() && std::isspace(source[position])) {
    ++position;
  }
}