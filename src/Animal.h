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
#include <memory>
#include <iostream>
#include "Drawable.h"
#include "Statistics.h"
#include "Movement.h"

class Map;

enum class AnimalSpecies {
	CARNIVORE,
	HERBIVORE
};

class Animal : public Drawable {
private:
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;

	static float SizeInPixels_;

public:
	Animal() {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	Animal(FPoint xy) : Drawable(xy) {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	Trait getEnergy() const {
		return Statistics_.Energy;
	}

	Trait getSize() const {
		return Statistics_.Size;
	}

	Trait getSpeed() const {
		return Statistics_.Speed;
	}
	virtual void click() override { std::cout << "ANIMAL CLICKED!\n"; }
	virtual AnimalSpecies getSpecies() const = 0;

	friend Map;
};
