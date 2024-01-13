// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Animal.h"
#include "Simulation.h"
#include "Random.h"

FPoint Animal::getRealSize() {
	return Size_ * Statistics_.Size;
}

bool Animal::shoulDie() {
	return Statistics_.Energy < 0.01f;
}
void Animal::shiftPosition(FPoint offset) {
	Point map_size = Parent_.getMap().getMapSize();
	FPoint real_size = getRealSize();
	Position_ += offset;
	if (Position_.X < 0.f)
		Position_.X = 0.f;
	else if (Position_.X > map_size.X - real_size.X)
		Position_.X = map_size.X - real_size.X;
	if (Position_.Y < 0.f)
		Position_.Y = 0.f;
	else if (Position_.Y > map_size.Y - real_size.Y)
		Position_.Y = map_size.Y - real_size.Y;
}
void Animal::eat(Drawable& object) {
	if (!reproduce())
		Statistics_.Energy = 100.f;
	Parent_.getMap().removeObject(object);
}
bool Animal::reproduce() {
	if (Statistics_.Energy > 50.f) {
		float size = Statistics_.Size + getRandomFloat(-SIZE_DIFF, SIZE_DIFF);
		float speed = Statistics_.Speed + getRandomFloat(-SPEED_DIFF, SPEED_DIFF);
		float x = Position_.X + getRandomFloat(-20.f, 20.f);
		float y = Position_.Y + getRandomFloat(-20.f, 20.f);
		Parent_.getMap().addAnimal(FPoint(x, y),
			Parent_, 50.f, speed, size, getSpecies());
		return true;
	}
	return false;
}
bool Animal::move(long long milliseconds) {
	if (AnimalMovement_) {
		float energy_usage = AnimalMovement_->move(
			Parent_.getMap(), *this, milliseconds / 1000.f);
		Statistics_.Energy -= energy_usage / LIFE_SPAN;
	}
	return true;
}
void Animal::click() {
	Parent_.select(*this);
}
void Animal::whenSelected() {
	Parent_.bindAnimalStatistics(*this);
	Parent_.showAnimalMenu();
}
void Animal::whenUnselected() {
	Parent_.hideAnimalMenu();
}
void Animal::draw(SDL_Renderer* renderer, FPoint offset) {
	SDL_SetRenderDrawColor(renderer, Color_.r, Color_.g, Color_.b, Color_.a);
	SDL_FRect rect;
	rect.x = offset.X + Position_.X;
	rect.y = offset.Y + Position_.Y;
	rect.w = Size_.X * Statistics_.Size;
	rect.h = Size_.Y * Statistics_.Size;
	SDL_RenderFillRectF(renderer, &rect);
}

bool Animal::isMouseOver(FPoint mouse_pos) const {
	return mouse_pos >= Position_ &&
		mouse_pos <= Position_ + Size_ * Statistics_.Size;
}
