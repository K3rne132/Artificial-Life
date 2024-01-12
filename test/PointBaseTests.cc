// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "pch.h"
#include <PointBase.hpp>


TEST(PointBaseTests, AssignOperatorTest) {
	Point p1(1, 2);
	Point p2(100, 200);

	p1 = p2;

	EXPECT_EQ(Point(p1.X, p1.Y), Point(p2.X, p2.Y));
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

TEST(PointBaseTests, LessOperatorTest) {
	Point p1(2, 3);
	Point p2(1, 6);
	Point p3(-1, -10);
	Point p4(-1, -10);

	EXPECT_TRUE(p3 < p1);
	EXPECT_FALSE(p1 < p2);
	EXPECT_FALSE(p4 < p3);
}

TEST(PointBaseTests, GreatOperatorTest) {
	Point p1(2, 3);
	Point p2(1, 1);
	Point p3(-1, 10);
	Point p4(-1, -10);

	EXPECT_TRUE(p1 > p2);
	EXPECT_FALSE(p3 > p1);
	EXPECT_TRUE(p1 > p4);
}

TEST(PointBaseTests, GreatEqOperatorTest) {
	Point p1(4, 3);
	Point p2(1, 3);
	Point p3(0, 0);
	Point p4(0, 0);

	EXPECT_TRUE(p1 >= p2);
	EXPECT_TRUE(p3 >= p4);
	EXPECT_FALSE(p4 >= p2);
}

TEST(PointBaseTests, LessEqOperatorTest) {
	Point p1(-5, 0);
	Point p2(-5, 3);
	Point p3(-2, 3);
	Point p4(-2, 3);

	EXPECT_TRUE(p1 <= p2);
	EXPECT_TRUE(p3 <= p4);
	EXPECT_FALSE(p4 <= p2);
}

TEST(PointBaseTests, PlusEqOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p1.X + p2.X;
	int y_res = p1.Y + p2.Y;

	p2 += p1;

	EXPECT_EQ(Point(x_res, y_res), Point(p2.X, p2.Y));
	EXPECT_EQ(p1, Point(1, 9));
}

TEST(PointBaseTests, MinEqOperatorTest) {
	Point p1(1, 9);
	Point p2(5, 8);

	int x_res = p2.X - p1.X;
	int y_res = p2.Y - p1.Y;

	p2 -= p1;

	EXPECT_EQ(Point(x_res, y_res), Point(p2.X, p2.Y));
	EXPECT_EQ(p1, Point(1, 9));
}

TEST(PointBaseTests, PlusOperatorTest) {
	Point p1(-10, 3);
	Point p2(-5, 8);

	int x_res = p1.X + p2.X;
	int y_res = p1.Y + p2.Y;

	Point res = p1 + p2;

	EXPECT_EQ(Point(x_res, y_res), Point(res.X, res.Y));
}

TEST(PointBaseTests, MinusOperatorTest) {
	Point p1(5, 1);
	Point p2(-1, 3);

	int x_res = p1.X - p2.X;
	int y_res = p1.Y - p2.Y;

	Point res = p1 - p2;

	EXPECT_EQ(Point(x_res, y_res), Point(res.X, res.Y));
}

TEST(PointBaseTests, MultEqOperatorTest) {
	Point p1(-10, 2);
	int scalar = 2;

	int x_res = p1.X * scalar;
	int y_res = p1.Y * scalar;

	p1 *= scalar;

	EXPECT_EQ(Point(x_res, y_res), Point(p1.X, p1.Y));
}

TEST(PointBaseTests, DivEqOperator) {
	Point p1(25, -10);
	float scalar = 2.5;

	float x_res = p1.X / scalar;
	float y_res = p1.Y / scalar;

	p1 /= scalar;

	EXPECT_EQ(Point(x_res, y_res), Point(p1.X, p1.Y));
}

TEST(PointBaseTests, MultOperatorTest) {
	Point p1(1, 3);
	int scalar = 5;

	int x_res = p1.X * scalar;
	int y_res = p1.Y * scalar;

	Point res = p1 * scalar;

	EXPECT_EQ(Point(x_res, y_res), Point(res.X, res.Y));
}

TEST(PointBaseTests, DivOperatorTest) {
	Point p1(25, -10);
	float scalar = 2.5;

	float x_res = p1.X / scalar;
	float y_res = p1.Y / scalar;

	Point res = p1 / scalar;

	EXPECT_EQ(Point(x_res, y_res), Point(res.X, res.Y));
}

TEST(PointBaseTests, OppOperatorTest) {
	Point p1(2, -3);

	float x_res = -p1.X;
	float y_res = -p1.Y;

	Point res = !p1;

	EXPECT_EQ(Point(x_res, y_res), Point(res.X, res.Y));
	EXPECT_EQ(p1, Point(2, -3));
}

TEST(PointBaseTests, NormTest) {
	FPoint p1(3, 4);
	float expected_norm = 5.0;

	EXPECT_EQ(expected_norm, p1.norm());
}