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
#include "Button.h"
#include "TextValue.hpp"

class Animal;
class Simulation;

using ButtonVector = std::vector<std::unique_ptr<Button>>;

class Menu {
private:
	ButtonVector MenuElements_;

	// Animal interface elements
	FTextValue* Energy_;
	FTextValue* Speed_;
	FTextValue* Size_;

public:
	Menu() : Energy_(nullptr), Speed_(nullptr), Size_(nullptr) {}

	inline auto begin() const { return MenuElements_.begin(); }
	inline auto end() const { return MenuElements_.end(); }
	void addIndependentMenuElement(std::unique_ptr<Button>& menu_obj);
	void addMainMenuElement(std::unique_ptr<Button>& menu_obj);
	void addAnimalMenuElement(std::unique_ptr<Button>& menu_obj);
	void createAnimalInterface(Simulation& simulation);
	void createMainInterface(Simulation& simulation);
	void bindStatistics(Animal& animal);
};
