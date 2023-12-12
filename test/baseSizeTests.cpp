#include "pch.h"
#include <baseSize.hpp>

TEST(baseSizeTests, AssignOperatorTest) {
	baseSize s1(1080, 1920);
	baseSize s2(100, 200);

	s1 = s2;

	EXPECT_EQ(s1.Width, s2.Width);
	EXPECT_EQ(s1.Height, s2.Height);
}