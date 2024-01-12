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

static int getRandomInt(int min, int max) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

static int getRandomInt(int max) {
	return getRandomInt(0, max);
}

static float getRandomFloat(float min, float max) {
	int diff = max - min;
	int rand = getRandomInt(diff * 1000);
	return static_cast<float>(rand) / 1000.f + min;
}

static float getRandomFloat(float max) {
	return getRandomFloat(0, max);
}
