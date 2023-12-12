#pragma once
#include "pch.h"
#include <basePoint.hpp>
using Point = basePoint<unsigned long>;
using FPoint = basePoint<float>;

class FixtureBasePointTests : public testing::Test {
protected:
	Point p1 = Point(1, 1);
	Point p2 = Point(2, 2);
	Point p3 = Point(3, 3);

	void SetUp() override {
	}

	void TearDown() override {}
};