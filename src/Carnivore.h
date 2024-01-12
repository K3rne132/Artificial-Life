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
	inline static SDL_Color Color = RED;

public:
	inline static unsigned int Count = 0;

	Carnivore() {
		setColor(Color);
		++Count;
	}
	Carnivore(FPoint xy) : Animal(xy) {
		setColor(Color);
	}
	~Carnivore() {
		--Count;
	}
	virtual AnimalSpecies getSpecies() const override { return AnimalSpecies::CARNIVORE; }
};
