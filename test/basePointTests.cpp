#include "pch.h"
#include "FixtureBasePointTests.h"

TEST(basePointTests, AssignOperatorTest) {
	Point p1(1, 2);
	Point p2(100, 200);

	p1 = p2;

	EXPECT_EQ(p1.X, p2.X);
	EXPECT_EQ(p1.Y, p2.Y);
}

TEST(basePointTests, EqOperatorTest) {
	Point p1(1, 1);
	Point p2(1, 1);

	EXPECT_TRUE(p1 == p2);
}

TEST(basePointTests, IneqOperatorTest) {
	Point p1(1, 1);
	Point p2(1, 0);

	EXPECT_TRUE(p1 != p2);
}

TEST(basePointTests, AddOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p1.X + p2.X;
	int y_res = p1.Y + p2.Y;

	p2 += p1;

	EXPECT_EQ(x_res, p2.X);
	EXPECT_EQ(y_res, p2.Y);
}

TEST(basePointTests, SubOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p2.X - p1.X;
	int y_res = p2.Y - p1.Y;

	p2 -= p1;

	EXPECT_EQ(x_res, p2.X);
	EXPECT_EQ(y_res, p2.Y);
}

TEST(basePointTests, NormTest) {
	FPoint p1(3, 4);
	float expected_norm = 5.0;

	EXPECT_EQ(expected_norm, p1.norm());
}