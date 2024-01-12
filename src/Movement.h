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
#include <limits>
#include "Map.h"

class Animal;
class Carnivore;
class Herbivore;
class Plant;
class Statistics;

const float F_MAX = std::numeric_limits<float>::max();

struct Nearest {
	Carnivore* Carnivore_;
	// distance to carnivore
	float      CDistance_;
	Herbivore* Herbivore_;
	// distance to herbivore
	float      HDistance_;
	Plant*     Plant_;
	// distance to plant
	float      PDistance_;
	Nearest() : Carnivore_(nullptr), Herbivore_(nullptr), Plant_(nullptr),
		CDistance_(F_MAX), HDistance_(F_MAX), PDistance_(F_MAX) {
	}
};

class Movement {
protected:
	static const int SIGHT = 600.f;

	Nearest getNearest(Map& map, FPoint from) const;
	Statistics& getStatistics(Animal& animal) const;

public:
	virtual float move(Map& map, Animal& animal, float time_scale) = 0;
};
