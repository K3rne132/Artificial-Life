// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "MovementCarnivore.h"
#include "Herbivore.h"

float MovementCarnivore::move(Map& map, Animal& animal, float time_scale) {
	FPoint animal_center = animal.getCenter() - animal.getSize() / 2;
	Statistics stats = getStatistics(animal);
	if (Nearest_.Herbivore_ && // if found edible animal in sight
		Nearest_.Herbivore_->getRealSize() < animal.getRealSize() * 1.1f) {
		Direction_ = NONE;
		FPoint diff = Nearest_.Herbivore_->getCenter() - animal.getCenter();
		if (diff.norm() < animal.getRealWidth() / 2) {
			animal.eat(*Nearest_.Herbivore_);
			return 0.f;
		}
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		if (Nearest_.HDistance_ > distance) {
			float scale = distance / Nearest_.HDistance_;
			animal.shiftPosition(diff * scale);
			return diff.norm() * scale * stats.Speed;
		}
		distance = Nearest_.HDistance_ * time_scale;
		animal.shiftPosition(diff);
		return diff.norm() * stats.Speed;
	}
	else { // if no edible animals randomize path
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		FPoint offset = randomizeDirection(distance);
		animal.shiftPosition(offset);
		return distance * stats.Speed;
	}
}
