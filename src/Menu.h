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

template <typename T>
class TextValue;
class TextInput;
class Animal;
class Simulation;

using ButtonVector = std::vector<std::unique_ptr<Button>>;

class Menu {
private:
	ButtonVector MenuElements_;

	// Main interface elements
	TextInput* FilePath_;

	// Animal interface elements
	TextValue<float>* Energy_;
	TextValue<float>* Speed_;
	TextValue<float>* Size_;

public:
	Menu() : FilePath_(nullptr), Energy_(nullptr), Speed_(nullptr),
		Size_(nullptr) {}

	inline auto begin() const { return MenuElements_.begin(); }
	inline auto end() const { return MenuElements_.end(); }
	// Add element to menu without assigning to group (group NONE)
	void addIndependentMenuElement(std::unique_ptr<Button> menu_obj);
	// Add element to menu and assign to MAINMENU group
	void addMainMenuElement(std::unique_ptr<Button> menu_obj);
	// Add element to menu and assign to ANIMALMENU group
	void addAnimalMenuElement(std::unique_ptr<Button> menu_obj);
	// Executes a sequence of commands to create a animal menu
	void createAnimalInterface(Simulation& simulation);
	// Executes a sequence of commands to create a main menu
	void createMainInterface(Simulation& simulation);
	// Bind animal statistics to be displayed
	void bindStatistics(Animal& animal);
};
