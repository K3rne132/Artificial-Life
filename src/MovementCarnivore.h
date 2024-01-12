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
#include "Movement.h"
#include "Herbivore.h"

class MovementCarnivore : public Movement {
public:
	virtual float move(Map& map, Animal& animal, float time_scale) override {
		FPoint animal_center = animal.getPosition() - animal.getSize() / 2;
		Nearest nearest = getNearest(map, animal_center);
		Statistics stats = getStatistics(animal);
		if (nearest.Herbivore_) {
			FPoint diff = nearest.Herbivore_->getPosition() - animal.getPosition();
			float distance = Animal::BaseSpeed_ * stats.Speed / stats.Size * time_scale;
			if (nearest.HDistance_ > distance) {
				float scale = distance / nearest.HDistance_;
				animal.shiftPosition(diff * scale);
				return diff.norm() * scale * stats.Speed / 10.f;
			}
			distance = nearest.HDistance_ * time_scale;
			animal.shiftPosition(diff);
			return diff.norm() * stats.Speed / 10.f;
		}
		return 0.f;
	}
};
