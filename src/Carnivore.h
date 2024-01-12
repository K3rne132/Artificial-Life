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
#include "MovementCarnivore.h"

class Carnivore : public Animal {
private:
	inline static SDL_Color Color = RED;

public:
	inline static unsigned int Count = 0;

	Carnivore(Simulation& parent) : Animal(parent) {
		AnimalMovement_ = std::unique_ptr<Movement>(new MovementCarnivore());
		setColor(Color);
		++Count;
	}
	Carnivore(FPoint xy, Simulation& parent) : Animal(xy, parent) {
		Statistics_.Speed = 4.f;
		AnimalMovement_ = std::unique_ptr<Movement>(new MovementCarnivore());
		setColor(Color);
		++Count;
	}
	~Carnivore() { --Count; }
};
