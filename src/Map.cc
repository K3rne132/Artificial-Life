// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "Map.h"
#include "Animal.h"
#include "Plant.h"
#include "Random.h"
#include "Carnivore.h"
#include "Herbivore.h"

using json = nlohmann::json;

bool Map::addObject(std::unique_ptr<Drawable>& map_object) {
	Objects_.push_back(std::move(map_object));
	return true;
}

bool Map::removeObject(Drawable& map_object) {
	auto it = std::find_if(Objects_.begin(), Objects_.end(),
		[&map_object](const std::unique_ptr<Drawable>& ptr) {
			return ptr.get() == &map_object;
		});
	if (it != Objects_.end()) {
		Objects_.erase(it);
		return true;
	}
	return false;
}

Drawable& Map::operator[](size_t index) const {
	if (index >= Objects_.size()) {
		throw std::out_of_range("Index out of bounds!");
	}
	return *Objects_[index].get();
}

Point Map::getMapSize() const {
	return Size_;
}

size_t Map::getSize() const { 
	return Objects_.size(); 
}

bool Map::readFromFile(const std::string& filename){
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Failed to open the file: " << filename << std::endl;
		return false;
	}

	json jsonData = json::parse(inFile);

	auto herbi = jsonData.at("herbivores");
	auto carni = jsonData.at("carnivores");
	auto plant = jsonData.at("plants");

	for (int i = 0; i < carni.size(); i++) {
		int pointX = carni[i].at("position").at("X");
		int pointY = carni[i].at("position").at("Y");
		FPoint point(pointX, pointY);
		auto carnivore = std::unique_ptr<Drawable>(new Carnivore(point));
		Animal* anim = dynamic_cast<Animal*>(carnivore.get());
		addObject(carnivore);
		anim->Statistics_.Energy = carni[i].at("energy");
		anim->Statistics_.Size = carni[i].at("size");
		anim->Statistics_.Speed = carni[i].at("speed");
	}

	for (int i = 0; i < herbi.size(); i++) {
		int pointX = herbi[i].at("position").at("X");
		int pointY = herbi[i].at("position").at("Y");
		FPoint point(pointX, pointY);
		auto herbivore = std::unique_ptr<Drawable>(new Herbivore(point));
		Animal* anim = dynamic_cast<Animal*>(herbivore.get());
		addObject(herbivore);
		anim->Statistics_.Energy = herbi[i].at("energy");
		anim->Statistics_.Size = herbi[i].at("size");
		anim->Statistics_.Speed = herbi[i].at("speed");
	}

	for (int i = 0; i < plant.size(); i++) {
		int pointX = plant[i].at("position").at("X");
		int pointY = plant[i].at("position").at("Y");
		FPoint point(pointX, pointY);
		auto plant1 = std::unique_ptr<Drawable>(new Plant(point));
		Plant* pl = dynamic_cast<Plant*>(plant1.get());
		addObject(plant1);
		pl->NutritionalValue_ = plant[i].at("nutritionalValue");
	}

	inFile.close();
	return true;
}

bool Map::writeToFile(const std::string& filename) {

	std::ofstream outFile(filename);

	if (!outFile.is_open()) {
		std::cerr << "Failed to open the file for writing: " << filename << std::endl;
		return false;
	}

	int i = 0;
	json object_data;
	object_data = {
		{"height", Size_.X},
		{"width", Size_.Y}
	};
	json animal_object;
	for (const auto& obj : Objects_) {
		obj->getPosition();
		Animal* anim = dynamic_cast<Animal*>(obj.get());

		Plant* plant = dynamic_cast<Plant*>(obj.get());
		if (anim) {
			animal_object = {
				{"size", anim->getSize().getCurrent()},
				{"energy", anim->getEnergy().getCurrent()},
				{"speed", anim->getSpeed().getCurrent()},
				{"position", {
					{"X", anim->getPosition().X},
					{"Y", anim->getPosition().Y}
			}}
			};
			auto animalType = anim->getSpecies();
			if (animalType == AnimalSpecies::CARNIVORE) {
				object_data["carnivores"].push_back(animal_object);
			}
			else if (animalType == AnimalSpecies::HERBIVORE) {
				object_data["herbivores"].push_back(animal_object);
			}
		}
		else if (plant) {
			object_data["plants"] += {
				{"nutritionalValue", plant->getNutritionalValue()},
				{"position", {
					{"X", plant->getPosition().X},
					{"Y", plant->getPosition().Y}
				}}
			};
		}
	}
	
	outFile << std::setw(4) << object_data;

	outFile.close();
	return true;
}

bool Map::generate(int carnivores, int herbivores, int plants, int height, int width) {
	Size_ = Point(width, height);

	for (int i = 0; i < carnivores; i++) {
		FPoint point(getRandom(0, width), getRandom(0, height));
		auto carnivore = std::unique_ptr<Drawable>(new Carnivore(point));
		Animal* anim = dynamic_cast<Animal*>(carnivore.get());
		addObject(carnivore);
		anim->Statistics_.Energy = getRandom(0, 100)/1.f;
		anim->Statistics_.Size = getRandom(25, 400)/100.f;
		anim->Statistics_.Speed = getRandom(5, 20)/10.f;
	}

	for (int i = 0; i < herbivores; i++) {
		FPoint point(getRandom(0, width), getRandom(0, height));
		auto herbivore = std::unique_ptr<Drawable>(new Herbivore(point));
		Animal* anim = dynamic_cast<Animal*>(herbivore.get());
		addObject(herbivore);
		anim->Statistics_.Energy = getRandom(0, 100) / 1.f;
		anim->Statistics_.Size = getRandom(25, 400) / 100.f;
		anim->Statistics_.Speed = getRandom(5, 20) / 10.f;
	}

	for (int i = 0; i < plants; i++) {
		FPoint point(getRandom(0, width), getRandom(0, height));
		auto plant = std::unique_ptr<Drawable>(new Plant(point));
		Plant* pl = dynamic_cast<Plant*>(plant.get());
		addObject(plant);
		pl->NutritionalValue_ = getRandom(0, 5) / 1.f;
	}
	return true;
}
