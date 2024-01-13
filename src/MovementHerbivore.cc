// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "MovementHerbivore.h"
#include "Plant.h"
#include "Carnivore.h"

bool MovementHerbivore::goEat(Nearest& n, Animal& animal) {
	if (n.Plant_) {
		if (!n.Carnivore_)
			return true;
		else if (n.Carnivore_) {
			if (n.Carnivore_->getRealSize() < animal.getRealSize() * 1.05f)
				return true;
			else if (n.PDistance_ < n.CDistance_)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool MovementHerbivore::goRun(Nearest& n, Animal& animal) {
	if (n.Carnivore_) {
		if (n.Carnivore_->getRealSize() > animal.getRealSize() * 1.05f)
			return true;
	}
	return false;
}

float MovementHerbivore::move(Map& map, Animal& animal, float time_scale) {
	FPoint animal_center = animal.getPosition() - animal.getSize() / 2;
	Nearest nearest = getNearest(map, animal_center);
	Statistics stats = getStatistics(animal);
	if (goEat(nearest, animal)) {
		Direction_ = NONE;
		FPoint diff = nearest.Plant_->getPosition() - animal.getPosition();
		if (diff.norm() < Animal::SIZE) {
			animal.eat(*nearest.Plant_);
			return 0.f;
		}
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		if (nearest.PDistance_ > distance) {
			float scale = distance / nearest.PDistance_;
			animal.shiftPosition(diff * scale);
			return diff.norm() * scale * stats.Speed;
		}
		distance = nearest.PDistance_ * time_scale;
		animal.shiftPosition(diff);
		return diff.norm() * stats.Speed;
	}
	else if (goRun(nearest, animal)) {
		Direction_ = NONE;
		if (nearest.Plant_) {
			FPoint diff = nearest.Plant_->getPosition() - animal.getPosition();
			if (diff.norm() < Animal::SIZE) {
				animal.eat(*nearest.Plant_);
				return 0.f;
			}
		}
		FPoint diff = nearest.Carnivore_->getPosition() - animal.getPosition();
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		float scale = distance / nearest.CDistance_;
		animal.shiftPosition(!diff * scale);
		return diff.norm() * scale * stats.Speed;
	}
	else { // if no edible animals randomize path
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		FPoint offset = randomizeDirection(distance);
		animal.shiftPosition(offset);
		return distance * stats.Speed;
	}
}
