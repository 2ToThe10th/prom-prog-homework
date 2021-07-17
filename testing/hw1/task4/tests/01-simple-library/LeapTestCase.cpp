//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST_F(LeapTestCase, Negative) {
  EXPECT_THROW(IsLeap(-1), std::invalid_argument);
}

TEST_F(LeapTestCase, Zero) {
  EXPECT_THROW(IsLeap(0), std::invalid_argument);
}

TEST_F(LeapTestCase, NotDividedBy4) {
  EXPECT_EQ(IsLeap(2003), false);
}

TEST_F(LeapTestCase, DividedBy4ButNot100) {
  EXPECT_EQ(IsLeap(2004), true);
}

TEST_F(LeapTestCase, DividedBy100ButNot400) {
  EXPECT_EQ(IsLeap(2100), false);
}

TEST_F(LeapTestCase, DividedBy400) {
  EXPECT_EQ(IsLeap(2000), true);
}