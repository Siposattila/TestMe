#include "class.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>

// Test parsing a simple class
TEST(ParserTest, TestParseClassWithMethod) {
  std::string code = "class MyClass { void myMethod() { int x; } }";
  Lexer lexer(code);
  Parser parser(lexer);

  // Parse the class
  std::shared_ptr<Class> clazz = parser.parseClass();

  // Check class name
  ASSERT_EQ(clazz->getName(), "MyClass");

  // Check method
  ASSERT_EQ(clazz->getMethods().size(), 1);
  ASSERT_EQ(clazz->getMethods()[0]->getName(), "myMethod");

  // Check variables
  ASSERT_EQ(clazz->getVariables().size(), 1);
  ASSERT_EQ(clazz->getVariables()[0]->getName(), "x");
}

// Test parsing a class without any methods or variables
TEST(ParserTest, TestParseEmptyClass) {
  std::string code = "class EmptyClass { }";
  Lexer lexer(code);
  Parser parser(lexer);

  // Parse the class
  std::shared_ptr<Class> clazz = parser.parseClass();

  // Check class name
  ASSERT_EQ(clazz->getName(), "EmptyClass");

  // Ensure no methods or variables
  ASSERT_EQ(clazz->getMethods().size(), 0);
  ASSERT_EQ(clazz->getVariables().size(), 0);
}

// Test parsing a class with multiple variables
TEST(ParserTest, TestParseClassWithMultipleVariables) {
  std::string code = "class MyClass { int x; int y; }";
  Lexer lexer(code);
  Parser parser(lexer);

  // Parse the class
  std::shared_ptr<Class> clazz = parser.parseClass();

  // Check class name
  ASSERT_EQ(clazz->getName(), "MyClass");

  // Check variables
  ASSERT_EQ(clazz->getVariables().size(), 2);
  ASSERT_EQ(clazz->getVariables()[0]->getName(), "x");
  ASSERT_EQ(clazz->getVariables()[1]->getName(), "y");

  // Ensure no methods
  ASSERT_EQ(clazz->getMethods().size(), 0);
}

// Test parsing a class with multiple methods
TEST(ParserTest, TestParseClassWithMultipleMethods) {
  std::string code = "class MyClass { void method1() {}; void method2() {}; }";
  Lexer lexer(code);
  Parser parser(lexer);

  // Parse the class
  std::shared_ptr<Class> clazz = parser.parseClass();

  // Check class name
  ASSERT_EQ(clazz->getName(), "MyClass");

  // Check methods
  ASSERT_EQ(clazz->getMethods().size(), 2);
  ASSERT_EQ(clazz->getMethods()[0]->getName(), "method1");
  ASSERT_EQ(clazz->getMethods()[1]->getName(), "method2");

  // Ensure no variables
  ASSERT_EQ(clazz->getVariables().size(), 0);
}