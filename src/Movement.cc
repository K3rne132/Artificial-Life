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

Statistics& Movement::getStatistics(Animal& animal) const {
	return animal.Statistics_;
}

Nearest Movement::getNearest(Map& map, FPoint from) const {
	Nearest result;
	for (auto& obj : map) {
		Carnivore* carn = dynamic_cast<Carnivore*>(obj.get());
		if (carn) {
			float distance = (from - carn->getPosition()).norm();
			if (distance < SIGHT && distance < result.CDistance_) {
				result.Carnivore_ = carn;
				result.CDistance_ = distance;
			}
			continue;
		}
		Herbivore* herb = dynamic_cast<Herbivore*>(obj.get());
		if (herb) {
			float distance = (from - herb->getPosition()).norm();
			if (distance < SIGHT && distance < result.HDistance_) {
				result.Herbivore_ = herb;
				result.HDistance_ = distance;
			}
			continue;
		}
		Plant* plant = dynamic_cast<Plant*>(obj.get());
		if (plant) {
			float distance = (from - plant->getPosition()).norm();
			if (distance < SIGHT && distance < result.HDistance_) {
				result.Plant_ = plant;
				result.PDistance_ = distance;
			}
		}
	}
	return result;
}
