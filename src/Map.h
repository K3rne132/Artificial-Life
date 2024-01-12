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
#include <vector>
#include <memory>
#include "Drawable.h"

class Simulation;

using DrawableVector = std::vector<std::unique_ptr<Drawable>>;

enum class AnimalSpecies {
	CARNIVORE,
	HERBIVORE
};

class Map {
private:
	Point Size_;
	DrawableVector Objects_;

	bool addRandomizedAnimal(std::unique_ptr<Drawable> animal);

public:
	Map() : Size_(0, 0) {}
	Map(int width, int height) : Size_(width, height) {}

	// Add animal to map with specified position and statistics
	bool addAnimal(FPoint xy, Simulation& simulation, float energy,
		float speed, float size, AnimalSpecies specie);
	// Add created object (representing animal of plant) to map objects
	bool addObject(std::unique_ptr<Drawable> map_object);
	// Remove object from map objects
	bool removeObject(Drawable& map_object);
	inline const auto begin() const { return Objects_.begin(); }
	inline const auto rbegin() const { return Objects_.rbegin(); }
	inline const auto end() const { return Objects_.end(); }
	inline const auto rend() const { return Objects_.rend(); }
	/*
	* Return object from map vector with specified index (may throw
	* std::out_of_range exception)
	*/
	Drawable& operator[](size_t index) const;
	// Returns map width and height
	Point getMapSize() const;
	// Return map objects count
	size_t getSize() const;
	// Read map from json file
	bool readFromFile(const std::string& filename, Simulation& simulation);
	// Store map data to json file
	bool writeToFile(const std::string& filename);
	// Generate map with specified values
	bool generate(int carnivores, int herbivores, int food, int height, int width,
		Simulation& simulation);
};
