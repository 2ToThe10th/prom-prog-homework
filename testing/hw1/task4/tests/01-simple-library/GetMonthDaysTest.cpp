//
// Created by 2ToThe10th on 03.05.2021.
//

#include "GetMonthDaysTest.h"

#include <Functions.h>

TEST_F(GetMonthDaysTest, NotInRangeMore) {
  EXPECT_THROW(GetMonthDays(2001, 13), std::invalid_argument);
}

TEST_F(GetMonthDaysTest, NotInRangeLess) {
  EXPECT_THROW(GetMonthDays(2001, 0), std::invalid_argument);
}

TEST_F(GetMonthDaysTest, NotInLeap) {
  const int DaysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  for (int i = 1; i < 13; ++i) {
    EXPECT_EQ(GetMonthDays(2001, i), DaysInMonth[i - 1]);
  }
}

TEST_F(GetMonthDaysTest, February) {
  EXPECT_EQ(GetMonthDays(2004, 2), 29);
}