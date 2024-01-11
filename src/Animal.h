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
#include "Simulation.h"

class Animal : public Drawable {
protected:
	Simulation& Parent_;
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;

	static float SizeInPixels_;

public:
	Animal(Simulation& parent) : Parent_(parent) {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	Animal(FPoint xy, Simulation& parent) : Parent_(parent), Drawable(xy) {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	virtual ~Animal() {
		Parent_.unselect(*this);
	}

	virtual void click() override { std::cout << "ANIMAL CLICKED!\n"; }
};
