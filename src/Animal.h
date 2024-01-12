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

class Map;

enum class AnimalSpecies {
	CARNIVORE,
	HERBIVORE
};

class Animal : public Drawable {
protected:
	Simulation&               Parent_;
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;

	inline static float SizeInPixels_ = 20.f;

public:
	inline static float BaseSpeed_ = 100.f;

	Animal(Simulation& parent) : Parent_(parent) {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	Animal(FPoint xy, Simulation& parent) : Parent_(parent), Drawable(xy) {
		setSize(FPoint(SizeInPixels_, SizeInPixels_) * Statistics_.Size);
	}
	virtual ~Animal() {
		Parent_.unselect(*this);
	}
	bool shoulDie() {
		return Statistics_.Energy < 0.01f;
	}
	void shiftPosition(FPoint offset) {
		Position_ += offset;
	}
	virtual bool move(long long milliseconds) {
		if (AnimalMovement_) {
			float energy_usage = AnimalMovement_->move(
				Parent_.getMap(), *this, milliseconds / 1000.f);
			Statistics_.Energy -= energy_usage;
		}
		return true;
	}
	virtual void click() override {
		Parent_.select(*this);
	}
	virtual void whenSelected() {
		Parent_.bindAnimalStatistics(*this);
		Parent_.showAnimalMenu();
	}
	virtual void whenUnselected() {
		Parent_.hideAnimalMenu();
	}
	virtual void draw(SDL_Renderer* renderer, FPoint offset) override {
		SDL_SetRenderDrawColor(renderer, Color_.r, Color_.g, Color_.b, Color_.a);
		SDL_FRect rect;
		rect.x = offset.X + Position_.X;
		rect.y = offset.Y + Position_.Y;
		rect.w = Size_.X * Statistics_.Size;
		rect.h = Size_.Y * Statistics_.Size;
		SDL_RenderFillRectF(renderer, &rect);
	}
	virtual AnimalSpecies getSpecies() const = 0;
	bool isMouseOver(FPoint mouse_pos) const {
		return mouse_pos >= Position_ &&
			mouse_pos <= Position_ + Size_ * Statistics_.Size;
	}

	friend Map;
	friend Movement;
	friend Menu;
};
