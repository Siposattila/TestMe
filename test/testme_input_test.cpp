#include <gtest/gtest.h>
#include <string>
#include <testme_input/code_input.hpp>
#include <testme_input/requirement_input.hpp>

TEST(CODE_INPUT_TEST, TestCodeInputRead) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ("namespace CSharpTutorials;\n", codeInput.getInput().c_str());
}

TEST(CODE_INPUT_TEST, TestCodeInputLanguageIsCorrectCSharp) {
  CodeInput codeInput("./data/input/example.cs");
  codeInput.processInput();

  ASSERT_TRUE(codeInput.getLanguage().impl == tree_sitter_c_sharp());
}

TEST(CODE_INPUT_TEST, TestCodeInputLanguageIsCorrectCpp) {
  CodeInput codeInput("./data/input/example.cpp");
  codeInput.processInput();

  ASSERT_TRUE(codeInput.getLanguage().impl == tree_sitter_cpp());
}

TEST(CODE_INPUT_TEST, TestCodeInputLanguageIsCorrectJava) {
  CodeInput codeInput("./data/input/example.java");
  codeInput.processInput();

  ASSERT_TRUE(codeInput.getLanguage().impl == tree_sitter_java());
}

TEST(CODE_INPUT_TEST, TestCodeInputGetParsedCode) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ(codeInput.getParsedCode().c_str(),
               "(compilation_unit (file_scoped_namespace_declaration name: "
               "(identifier)))");
}

TEST(CODE_INPUT_TEST, TestCodeInputFindFirstNodeByName) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ(std::string(codeInput.findFirstNodeByName("CSharpTutorials")
                               .getSourceRange(codeInput.getInput()))
                   .c_str(),
               "CSharpTutorials");
}

TEST(CODE_INPUT_TEST, TestCodeInputFindNodesByName) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ(std::string(codeInput.findNodesByName("CSharpTutorials")
                               .at(0)
                               .getSourceRange(codeInput.getInput()))
                   .c_str(),
               "CSharpTutorials");
}

TEST(CODE_INPUT_TEST, TestCodeInputGetParsedCodeByNode) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ(
      codeInput
          .getParsedCodeByNode(codeInput.findFirstNodeByName("CSharpTutorials"))
          .c_str(),
      "(identifier)");
}

TEST(CODE_INPUT_TEST, TestCodeInputGetCodeByNode) {
  CodeInput codeInput("./data/input/code.cs");
  codeInput.processInput();

  ASSERT_STREQ(
      codeInput.getCodeByNode(codeInput.findFirstNodeByName("CSharpTutorials"))
          .c_str(),
      "CSharpTutorials");
}

TEST(REQUIREMENT_INPUT_TEST, TestRequirementRead) {
  RequirementInput requirementInput("./data/input/requirement.txt");
  requirementInput.processInput();

  ASSERT_STREQ("In the Main method there should be variable string message. "
               "That should be printed out with Console.WriteLine.\n",
               requirementInput.getInput().c_str());
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
