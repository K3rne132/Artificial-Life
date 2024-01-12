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
#include "Movement.h"
#include "Statistics.h"
#include "Simulation.h"
#include "Map.h"

class Menu;

class Animal : public Drawable {
protected:
	Simulation&               Parent_;
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;
	
	inline static const float LIFE_SPAN = 10.f;
	inline static const float SIZE_DIFF = 0.1f;
	inline static const float SPEED_DIFF = 0.2f;

public:
	inline static const float SIZE = 20.f;
	inline static const float BASE_SPEED = 10.f;

	Animal(Simulation& parent) : Parent_(parent) {
		setSize(FPoint(SIZE, SIZE) * Statistics_.Size);
	}
	Animal(FPoint xy, Simulation& parent) : Parent_(parent), Drawable(xy) {
		setSize(FPoint(SIZE, SIZE) * Statistics_.Size);
	}
	virtual ~Animal() {
		Parent_.unselect(*this);
	}

	FPoint getRealSize();
	bool shoulDie();
	void shiftPosition(FPoint offset);
	void eat(Drawable& object);
	void reproduce();
	virtual bool move(long long milliseconds);
	virtual void click() override;
	virtual void whenSelected();
	virtual void whenUnselected();
	virtual void draw(SDL_Renderer* renderer, FPoint offset) override;
	virtual bool isMouseOver(FPoint mouse_pos) const;
	virtual AnimalSpecies getSpecies() const = 0;

	friend Map;
	friend Movement;
	friend Menu;
};
