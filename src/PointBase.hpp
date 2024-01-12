// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#pragma once
#include <cmath>
#include <SDL2/SDL.h>
#include <string>

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

	inline bool operator<(const PointBase& rhs) const {
		return (X < rhs.X && Y < rhs.Y);
	}

	inline bool operator>(const PointBase& rhs) const {
		return (X > rhs.X && Y > rhs.Y);
	}

	inline bool operator<=(const PointBase& rhs) const {
		return (X <= rhs.X && Y <= rhs.Y);
	}

	inline bool operator>=(const PointBase& rhs) const {
		return (X >= rhs.X && Y >= rhs.Y);
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

	inline PointBase& operator*=(const float rhs) {
		X *= rhs;
		Y *= rhs;
		return *this;
	}

	inline PointBase& operator/=(const float rhs) {
		X /= rhs;
		Y /= rhs;
		return *this;
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

	// Returns distance from this point to (0, 0) - length
	inline float norm() const {
		float res = std::hypot(X, Y);
		return res;
	}
};

using Point = PointBase<int>;
using FPoint = PointBase<float>;
