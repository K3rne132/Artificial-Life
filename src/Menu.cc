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
#include "TextInput.h"
#include "TextButton.h"
#include "Animal.h"
#include "Simulation.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "Plant.h"

void Menu::addIndependentMenuElement(std::unique_ptr<Button>& menu_obj) {
	menu_obj->setGroup(ButtonGroup::NONE);
	MenuElements_.push_back(std::move(menu_obj));
}

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
	auto remove = new TextButton(FPoint(950.f, 25.f), FPoint(100.f, 42.f),
		simulation, " USUN", [&simulation]() {simulation.removeSelectedAnimal(); }, RED);
	Energy_ = new FTextValue(FPoint(125.f, 25.f), simulation, "Energia: ");
	Speed_ = new FTextValue(FPoint(400.f, 25.f), simulation, "Szybkosc: ");
	Size_ = new FTextValue(FPoint(675.f, 25.f), simulation, "Rozmiar: ");
	addAnimalMenuElement(std::unique_ptr<Button>(remove));
	addAnimalMenuElement(std::unique_ptr<Button>(Energy_));
	addAnimalMenuElement(std::unique_ptr<Button>(Speed_));
	addAnimalMenuElement(std::unique_ptr<Button>(Size_));
}

void Menu::createMainInterface(Simulation& simulation) {
	auto toggle_menu = new TextButton(FPoint(10.f, 10.f), FPoint(238.f, 42.f),
		simulation, " Pokaz/Ukryj", [&simulation]() { simulation.toggleMainMenu(); });
	auto speed_down = new TextButton(FPoint(10.f, 250.f), FPoint(42.f, 42.f),
		simulation, " <<", [&simulation]() { simulation.speedDown(); });
	auto speed_up = new TextButton(FPoint(310.f, 250.f), FPoint(42.f, 42.f),
		simulation, " >>", [&simulation]() { simulation.speedUp(); });
	auto simulation_speed = new FTextValue(
		FPoint(60.f, 250.f), simulation, "Predkosc: ");
	simulation_speed->bindValue(&simulation.getSpeed(), 1);
	auto carnivore_count = new UITextValue(
		FPoint(10.f, 350.f), simulation, "Miesozercow: ");
	carnivore_count->bindValue(&Carnivore::Count);
	auto herbivore_count = new UITextValue(
		FPoint(10.f, 390.f), simulation, "Roslinozercow: ");
	herbivore_count->bindValue(&Herbivore::Count);
	auto plant_count = new UITextValue(
		FPoint(10.f, 430.f), simulation, "Roslin: ");
	plant_count->bindValue(&Plant::Count);
	addIndependentMenuElement(std::unique_ptr<Button>(toggle_menu));
	addMainMenuElement(std::unique_ptr<Button>(speed_down));
	addMainMenuElement(std::unique_ptr<Button>(speed_up));
	addMainMenuElement(std::unique_ptr<Button>(simulation_speed));
	addMainMenuElement(std::unique_ptr<Button>(carnivore_count));
	addMainMenuElement(std::unique_ptr<Button>(herbivore_count));
	addMainMenuElement(std::unique_ptr<Button>(plant_count));
}

void Menu::bindStatistics(Animal& animal) {
	Energy_->bindValue(animal.Statistics_.Energy.getCurrent());
	Speed_->bindValue(animal.Statistics_.Speed.getCurrent());
	Size_->bindValue(animal.Statistics_.Size.getCurrent());
}