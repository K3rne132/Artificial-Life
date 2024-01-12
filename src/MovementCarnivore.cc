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
	FPoint animal_center = animal.getPosition() - animal.getSize() / 2;
	Nearest nearest = getNearest(map, animal_center);
	Statistics stats = getStatistics(animal);
	if (nearest.Herbivore_ && // if found edible animal in sight
		nearest.Herbivore_->getRealSize() < animal.getRealSize() * 1.1f) {
		Direction_ = NONE;
		FPoint diff = nearest.Herbivore_->getPosition() - animal.getPosition();
		if (diff.norm() < Animal::SIZE) {
			animal.eat(*nearest.Herbivore_);
			return 0.f;
		}
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		if (nearest.HDistance_ > distance) {
			float scale = distance / nearest.HDistance_;
			animal.shiftPosition(diff * scale);
			return diff.norm() * scale * stats.Speed;
		}
		distance = nearest.HDistance_ * time_scale;
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
