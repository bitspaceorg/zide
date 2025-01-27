#include <gtest/gtest.h>

#include "../src/utils/zmath.h"

TEST(ADD_TWO_NUMBERS, POSITIVE_NUMBERS) {
  EXPECT_EQ(add_two_numbers(5, 2), 7);
  EXPECT_EQ(add_two_numbers(500, 2131), 2631);
}

TEST(ADD_TWO_NUMBERS, TWO_NEGATIVE_NUMBERS) {
  EXPECT_EQ(add_two_numbers(-5, -2), -7);
  EXPECT_EQ(add_two_numbers(-500, -2131), -2631);
}
