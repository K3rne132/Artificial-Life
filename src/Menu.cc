// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Menu.h"
#include "TextValue.h"
#include "TextInput.h"
#include "Animal.h"
#include "Simulation.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "Plant.h"

void Menu::addMainMenuElement(std::unique_ptr<Button>& menu_obj) {
	menu_obj->setGroup(ButtonGroup::MAINMENU);
	MenuElements_.push_back(std::move(menu_obj));
}

void Menu::addAnimalMenuElement(std::unique_ptr<Button>& menu_obj) {
	menu_obj->setGroup(ButtonGroup::ANIMALMENU);
	menu_obj->hide();
	MenuElements_.push_back(std::move(menu_obj));
}

void Menu::createAnimalInterface(Simulation& simulation) {
	Energy_ = new TextValue<float>(FPoint(150.f, 50.f), simulation, "Energia: ");
	Speed_ = new TextValue<float>(FPoint(500.f, 50.f), simulation, "Szybkosc: ");
	Size_ = new TextValue<float>(FPoint(850.f, 50.f), simulation, "Rozmiar: ");
	addAnimalMenuElement(std::unique_ptr<Button>(Energy_));
	addAnimalMenuElement(std::unique_ptr<Button>(Speed_));
	addAnimalMenuElement(std::unique_ptr<Button>(Size_));
}

void Menu::createMainInterface(Simulation& simulation) {
	auto elem1 = std::unique_ptr<Button>(
		new Button(FPoint(400.f, 100.f), FPoint(100.f, 100.f), BLUE, simulation));
	auto elem2 = std::unique_ptr<Button>(
		new TextInput(FPoint(400.f, 200.f), simulation, "random text input"));
	addMainMenuElement(elem1);
	addMainMenuElement(elem2);

	auto carnivore_count = new TextValue<unsigned int>(
		FPoint(50.f, 550.f), simulation, "Miesozercow: ");
	carnivore_count->bindValue(&Carnivore::Count);
	auto herbivore_count = new TextValue<unsigned int>(
		FPoint(50.f, 600.f), simulation, "Roslinozercow: ");
	herbivore_count->bindValue(&Herbivore::Count);
	auto plant_count = new TextValue<unsigned int>(
		FPoint(50.f, 650.f), simulation, "Roslin: ");
	plant_count->bindValue(&Plant::Count);
	addMainMenuElement(std::unique_ptr<Button>(carnivore_count));
	addMainMenuElement(std::unique_ptr<Button>(herbivore_count));
	addMainMenuElement(std::unique_ptr<Button>(plant_count));
}

void Menu::bindStatistics(Animal& animal) {
	Energy_->bindValue(animal.Statistics_.Energy.getCurrent());
	Speed_->bindValue(animal.Statistics_.Speed.getCurrent());
	Size_->bindValue(animal.Statistics_.Size.getCurrent());
}