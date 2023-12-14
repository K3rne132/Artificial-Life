#include "pch.h"
#include <PointBase.hpp>


TEST(PointBaseTests, AssignOperatorTest) {
	Point p1(1, 2);
	Point p2(100, 200);

	p1 = p2;

	EXPECT_EQ(p1.X, p2.X);
	EXPECT_EQ(p1.Y, p2.Y);
}

TEST(PointBaseTests, EqOperatorTest) {
	Point p1(1, 1);
	Point p2(1, 1);

	EXPECT_TRUE(p1 == p2);
}

TEST(PointBaseTests, IneqOperatorTest) {
	Point p1(1, 1);
	Point p2(1, 0);
	Point p3(1, 1);
	Point p4(0, 1);

	EXPECT_TRUE(p1 != p2);
	EXPECT_FALSE(p1 != p3);
	EXPECT_TRUE(p1 != p4);
}

TEST(PointBaseTests, PlusEqOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p1.X + p2.X;
	int y_res = p1.Y + p2.Y;

	p2 += p1;

	EXPECT_EQ(x_res, p2.X);
	EXPECT_EQ(y_res, p2.Y);
}

TEST(PointBaseTests, MinEqOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p2.X - p1.X;
	int y_res = p2.Y - p1.Y;

	p2 -= p1;

	EXPECT_EQ(x_res, p2.X);
	EXPECT_EQ(y_res, p2.Y);
}

TEST(PointBaseTests, PlusOperatorTest) {
	Point p1(-10, 3);
	Point p2(-5, 8);

	int x_res = p1.X + p2.X;
	int y_res = p1.Y + p2.Y;

	Point res = p1 + p2;

	EXPECT_EQ(x_res, res.X);
	EXPECT_EQ(y_res, res.Y);
}

TEST(PointBaseTests, MinusOperatorTest) {
	Point p1(5, 1);
	Point p2(-1, 3);

	int x_res = p1.X - p2.X;
	int y_res = p1.Y - p2.Y;

	Point res = p1 - p2;

	EXPECT_EQ(x_res, res.X);
	EXPECT_EQ(y_res, res.Y);
}

TEST(PointBaseTests, MultOperatorTest) {
	Point p1(1, 3);
	int scalar = 5;

	int x_res = p1.X * scalar;
	int y_res = p1.Y * scalar;

	Point res = p1 * scalar;

	EXPECT_EQ(x_res, res.X);
	EXPECT_EQ(y_res, res.Y);
}

TEST(PointBaseTests, DivOperatorTest) {
	Point p1(25, -10);
	float scalar = 2.5;

	float x_res = p1.X / scalar;
	float y_res = p1.Y / scalar;

	Point res = p1 / scalar;

	EXPECT_EQ(x_res, res.X);
	EXPECT_EQ(y_res, res.Y);
}

TEST(PointBaseTests, OppOperatorTest) {
	Point p1(2, -3);

	float x_res = -p1.X;
	float y_res = -p1.Y;

	Point res = !p1;

	EXPECT_EQ(x_res, res.X);
	EXPECT_EQ(y_res, res.Y);
}

TEST(PointBaseTests, NormTest) {
	FPoint p1(3, 4);
	float expected_norm = 5.0;

	EXPECT_EQ(expected_norm, p1.norm());
}