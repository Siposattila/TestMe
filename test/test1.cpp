#include <gtest/gtest.h>

TEST(TEST_TEST, TESTCMAKELOL) { ASSERT_EQ(1, 1); }
TEST(TEST_TEST, TESTCMAKELOL2) { ASSERT_EQ(1, 1); }

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
