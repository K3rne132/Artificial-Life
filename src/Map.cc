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
#include "Simulation.h"

using json = nlohmann::json;

bool Map::addRandomizedAnimal(std::unique_ptr<Drawable> animal) {
	Animal* anim = dynamic_cast<Animal*>(animal.get());
	if (!anim)
		return false;
	addObject(std::move(animal));
	anim->Statistics_.Energy = 100.f;
	anim->Statistics_.Size = getRandomFloat(0.5f, 2.f);
	anim->Statistics_.Speed = getRandomFloat(0.25f, 4.f);
	return true;
}

bool Map::addAnimal(FPoint xy, Simulation& simulation, float energy,
	float speed, float size, AnimalSpecies specie) {
	std::unique_ptr<Drawable> animal;
	if (specie == AnimalSpecies::CARNIVORE)
		animal = std::unique_ptr<Drawable>(new Carnivore(xy, simulation));
	else
		animal = std::unique_ptr<Drawable>(new Herbivore(xy, simulation));
	Animal* anim = dynamic_cast<Animal*>(animal.get());
	anim->Statistics_.Energy = energy;
	anim->Statistics_.Size = size;
	anim->Statistics_.Speed = speed;
	return addObject(std::move(animal));
}

bool Map::addObject(std::unique_ptr<Drawable> map_object) {
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

bool Map::readFromFile(const std::string& filename, Simulation& simulation) {
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
		addAnimal(point, simulation, carni[i].at("energy"), carni[i].at("speed"),
			carni[i].at("size"), AnimalSpecies::CARNIVORE);
	}

	for (int i = 0; i < herbi.size(); i++) {
		int pointX = herbi[i].at("position").at("X");
		int pointY = herbi[i].at("position").at("Y");
		FPoint point(pointX, pointY);
		addAnimal(point, simulation, herbi[i].at("energy"), herbi[i].at("speed"),
			herbi[i].at("size"), AnimalSpecies::HERBIVORE);
	}

	for (int i = 0; i < plant.size(); i++) {
		int pointX = plant[i].at("position").at("X");
		int pointY = plant[i].at("position").at("Y");
		FPoint point(pointX, pointY);
		auto plant1 = std::unique_ptr<Drawable>(new Plant(point));
		addObject(std::move(plant1));
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
				{"size", static_cast<float>(anim->Statistics_.Size)},
				{"energy", static_cast<float>(anim->Statistics_.Energy)},
				{"speed", static_cast<float>(anim->Statistics_.Speed)},
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

bool Map::generate(int carnivores, int herbivores, int plants, int height, int width,
	Simulation& simulation) {
	Size_ = Point(width, height);
	simulation.updateMap();

	for (int i = 0; i < carnivores; i++) {
		FPoint point(getRandomInt(width), getRandomInt(height));
		auto carnivore = std::unique_ptr<Drawable>(new Carnivore(point, simulation));
		addRandomizedAnimal(std::move(carnivore));
	}

	for (int i = 0; i < herbivores; i++) {
		FPoint point(getRandomInt(width), getRandomInt(height));
		auto herbivore = std::unique_ptr<Drawable>(new Herbivore(point, simulation));
		addRandomizedAnimal(std::move(herbivore));
	}

	for (int i = 0; i < plants; i++) {
		FPoint point(getRandomInt(width), getRandomInt(height));
		auto plant = std::unique_ptr<Drawable>(new Plant(point));
		addObject(std::move(plant));
	}
	return true;
}
