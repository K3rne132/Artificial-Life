#pragma once
#include <cmath>
#include <SDL2/SDL.h>

template <typename T>
class PointBase {
public:
	T X, Y;

	PointBase() : X(0), Y(0) {}
	PointBase(T x, T y) : X(x), Y(y) {}

	inline PointBase& operator=(const PointBase& rhs) {
		X = rhs.X;
		Y = rhs.Y;
		return *this;
	}

	inline bool operator==(const PointBase& rhs) const {
		return (X == rhs.X && Y == rhs.Y);
	}

	inline bool operator!=(const PointBase& rhs) const {
		return X != rhs.X || Y != rhs.Y;
	}

	inline PointBase& operator+=(const PointBase& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}

	inline PointBase& operator-=(const PointBase& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}

	inline PointBase operator+(const PointBase& rhs) const {
		auto copy = *this;
		copy.X += rhs.X;
		copy.Y += rhs.Y;
		return copy;
	}

	inline PointBase operator-(const PointBase& rhs) const {
		auto copy = *this;
		copy.X -= rhs.X;
		copy.Y -= rhs.Y;
		return copy;
	}

	inline PointBase operator*(const float rhs) const {
		auto copy = *this;
		copy.X *= rhs;
		copy.Y *= rhs;
		return copy;
	}

	inline PointBase operator/(const float rhs) const {
		auto copy = *this;
		copy.X /= rhs;
		copy.Y /= rhs;
		return copy;
	}

	inline PointBase operator!() const {
		auto copy = *this;
		copy.X = -copy.X;
		copy.Y = -copy.Y;
		return copy;
	}

	inline float norm() const {
		float res = sqrt(X * X + Y * Y);
		return res;
	}
};

using Point = PointBase<int>;
using FPoint = PointBase<float>;
