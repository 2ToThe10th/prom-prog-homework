#include <gtest/gtest.h>

#include "A/index.h"
#include "B/lib.h"

TEST(A, A) {
	EXPECT_EQ(A(), 1);
}

TEST(lib, B) {
	EXPECT_EQ(B(), 2);
}
