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
#include <random>

static std::default_random_engine rng;

// Returns random int in range(min, max)
static int getRandomInt(int min, int max) {
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

// Returns random int in range(0, max)
static int getRandomInt(int max) {
	return getRandomInt(0, max);
}

// Returns random float in range(min, max)
static float getRandomFloat(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

// Returns random float in range(0.f, max)
static float getRandomFloat(float max) {
	return getRandomFloat(0, max);
}
