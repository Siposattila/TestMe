#include <gtest/gtest.h>

TEST(TEST_TEST2, TESTCMAKE3) { ASSERT_EQ(1, 1); }
TEST(TEST_TEST2, TESTCMAKE4) { ASSERT_EQ(1, 1); }

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
