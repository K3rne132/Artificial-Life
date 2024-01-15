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
			if (n.Carnivore_->getRealSize() < animal.getRealSize() * 1.1f)
				return true;
			else if (n.CDistance_ < 2 * n.Carnivore_->getRealWidth())
				return false;
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
		if (n.Carnivore_->getRealSize() > animal.getRealSize() * 1.1f)
			return true;
	}
	return false;
}

float MovementHerbivore::move(Map& map, Animal& animal, float time_scale) {
	FPoint animal_center = animal.getCenter();
	Statistics stats = getStatistics(animal);
	if (goEat(Nearest_, animal)) {
		Direction_ = NONE;
		FPoint diff = Nearest_.Plant_->getCenter() - animal.getCenter();
		if (diff.norm() < animal.getRealWidth() / 2) {
			animal.eat(*Nearest_.Plant_);
			return 0.f;
		}
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		if (Nearest_.PDistance_ > distance) {
			float scale = distance / Nearest_.PDistance_;
			animal.shiftPosition(diff * scale);
			return diff.norm() * scale * stats.Speed;
		}
		distance = Nearest_.PDistance_ * time_scale;
		animal.shiftPosition(diff);
		return diff.norm() * stats.Speed;
	}
	else if (goRun(Nearest_, animal)) {
		Direction_ = NONE;
		if (Nearest_.Plant_) {
			FPoint diff = Nearest_.Plant_->getCenter() - animal.getCenter();
			if (diff.norm() < animal.getRealWidth() / 2) {
				animal.eat(*Nearest_.Plant_);
				return 0.f;
			}
		}
		FPoint diff = Nearest_.Carnivore_->getCenter() - animal.getCenter();
		float distance = Animal::BASE_SPEED * stats.Speed / stats.Size * time_scale;
		float scale = distance / Nearest_.CDistance_;
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
