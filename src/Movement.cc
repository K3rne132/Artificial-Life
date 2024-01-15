// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Movement.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "Plant.h"
#include "Random.h"

Statistics& Movement::getStatistics(Animal& animal) const {
	return animal.Statistics_;
}

Nearest Movement::getNearest(Map& map, FPoint from) const {
	Nearest result;
	for (size_t i = 0; i < map.getSize(); ++i) {
		Carnivore* carn = dynamic_cast<Carnivore*>(&map[i]);
		if (carn) {
			float distance = (from - carn->getPosition()).norm();
			if (distance < SIGHT && distance < result.CDistance_) {
				result.Carnivore_ = carn;
				result.CDistance_ = distance;
			}
			continue;
		}
		Herbivore* herb = dynamic_cast<Herbivore*>(&map[i]);
		if (herb) {
			float distance = (from - herb->getPosition()).norm();
			if (distance < SIGHT && distance < result.HDistance_) {
				result.Herbivore_ = herb;
				result.HDistance_ = distance;
			}
			continue;
		}
		Plant* plant = dynamic_cast<Plant*>(&map[i]);
		if (plant) {
			float distance = (from - plant->getPosition()).norm();
			if (distance < SIGHT && distance < result.PDistance_) {
				result.Plant_ = plant;
				result.PDistance_ = distance;
			}
		}
	}
	return result;
}

FPoint Movement::randomizeDirection(float distance) {
	if (Direction_ == NONE || Distance_ > 100.f) {
		Direction_ = getRandomFloat(2 * M_PI);
		Distance_ = 0.f;
	}
	Distance_ += distance;
	float tg = std::tan(Direction_);
	float x = distance / std::sqrt(1 + 1 / std::pow(tg, 2));
	float y = distance / std::sqrt(1 + std::pow(tg, 2));
	if (Direction_ < M_PI / 2)
		y = -y;
	else if (Direction_ > 3 * M_PI / 2) {
		x = -x;
		y = -y;
	}
	else if (Direction_ > M_PI) {
		x = -x;
	}
	return FPoint(x, y);
}

bool Movement::isRandom() {
	return std::abs(Direction_ - NONE) > 0.1f;
}

void Movement::updateNearest(Map& map, FPoint from) {
	Nearest_ = getNearest(map, from);
}

void Movement::removeNearest(Drawable& drawable) {
	if (Nearest_.Carnivore_ == &drawable) {
		Nearest_.Carnivore_ = nullptr;
		return;
	}
	if (Nearest_.Herbivore_ == &drawable) {
		Nearest_.Herbivore_ = nullptr;
		return;
	}
	if (Nearest_.Plant_ == &drawable) {
		Nearest_.Plant_ = nullptr;
		return;
	}
}
