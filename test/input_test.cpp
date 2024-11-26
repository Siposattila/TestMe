#include "../src/input/code_input.hpp"
#include "../src/input/requirement_input.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(INPUT_TEST, TestCodeInputRead) {
  CodeInput codeInput("./data/input/code.txt");
  codeInput.processInput();

  ASSERT_STREQ("namespace CSharpTutorials;\n", codeInput.getInput().c_str());
}

TEST(INPUT_TEST, TestRequirementRead) {
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
