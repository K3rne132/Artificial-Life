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
#include "Animal.h"
#include "Colors.h"
#include "MovementHerbivore.h"

class Herbivore : public Animal {
private:
	inline static SDL_Color Color = GREEN;

public:
	inline static unsigned int Count = 0;

	Herbivore(Simulation& parent) : Animal(parent) {
		AnimalMovement_ = std::unique_ptr<Movement>(new MovementHerbivore());
		setColor(Color);
		++Count;
	}
	Herbivore(FPoint xy, Simulation& parent) : Animal(xy, parent) {
		AnimalMovement_ = std::unique_ptr<Movement>(new MovementHerbivore());
		setColor(Color);
		++Count;
	}
	~Herbivore() { --Count; }

	virtual AnimalSpecies getSpecies() const override { return AnimalSpecies::HERBIVORE; }
};
