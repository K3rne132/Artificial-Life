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

class Carnivore : public Animal {
private:
	static SDL_Color Color;

public:
	static unsigned int Count;

	Carnivore(Simulation& parent) : Animal(parent) {
		setColor(Color);
		++Count;
	}
	Carnivore(FPoint xy, Simulation& parent) : Animal(xy, parent) {
		setColor(Color);
	}
	~Carnivore() {
		--Count;
	}
};

SDL_Color Carnivore::Color = RED;
unsigned int Carnivore::Count = 0;
