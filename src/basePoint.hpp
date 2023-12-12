#pragma once
#include <cmath>

template <typename T>
class basePoint {
public:
	T X, Y;

	basePoint() : X(0), Y(0) {

	}

	basePoint(T x, T y) : X(x), Y(y) {

	}

	inline basePoint& operator=(const basePoint& rhs) {
		X = rhs.X;
		Y = rhs.Y;
		return *this;
	}

	inline bool operator==(const basePoint& rhs) {
		return (X == rhs.X && Y == rhs.Y);
	}

	inline bool operator!=(const basePoint& rhs) {
		return !(X == rhs.X && Y == rhs.Y);
	}

	inline basePoint& operator+=(const basePoint& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}

	inline basePoint& operator-=(const basePoint& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}

	float norm() {
		float res = sqrt(X * X + Y * Y);
		return res;
	}
};