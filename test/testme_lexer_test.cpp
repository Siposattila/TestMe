#include <gtest/gtest.h>
#include <testme_lexer/lexer.hpp>

TEST(LexerTest, TestKeywordsAndIdentifiers) {
  std::string code = "class MyClass { void myMethod() { int x; } }";
  Lexer lexer(code);

  // Test for the first token: "class"
  Token token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::KEYWORD);
  ASSERT_EQ(token.value, "class");

  // Test for class name: "MyClass"
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::IDENTIFIER);
  ASSERT_EQ(token.value, "MyClass");

  // Test for opening brace
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, "{");

  // Test for method return type: "void"
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::KEYWORD);
  ASSERT_EQ(token.value, "void");

  // Test for method name: "myMethod"
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::IDENTIFIER);
  ASSERT_EQ(token.value, "myMethod");

  // Test for opening parenthesis
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, "(");

  // Test for closing parenthesis
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, ")");

  // Test for opening brace
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, "{");

  // Test for type: "int"
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::TYPE);
  ASSERT_EQ(token.value, "int");

  // Test for variable name: "x"
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::IDENTIFIER);
  ASSERT_EQ(token.value, "x");

  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, ";");

  // Test for closing brace
  token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::SYMBOL);
  ASSERT_EQ(token.value, "}");
}

// Test for handling an empty string
TEST(LexerTest, TestEmptyString) {
  std::string code = "";
  Lexer lexer(code);

  Token token = lexer.nextToken();
  ASSERT_EQ(token.type, TokenType::END_OF_FILE);
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
