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
#include <chrono>
#include "Controls.h"
#include "Menu.h"

class Window;
class Menu;
class Map;
class Controls;
class TextInput;
class Animal;

class Simulation {
private:
	Window&    Window_;
	Map&       Map_;
	SDL_Event  Event_;
	Camera     Camera_;
	Controls   Controls_;
	Menu&      Menu_;
	bool       Quit_;
	Button*    ButtonSelected_;
	TextInput* TextInputSelected_;
	Animal*    AnimalSelected_;
	float      Speed_;
	long long  PlantGeneration_;
	long long  TimeElapsedPlant_;
	bool       MainMenuHidden_;

	bool synchronize(long long time_diff);
	void dispatchEvent();
	void addMapBorder();
	void resetCamera();

public:
	Simulation(Window& window, Map& map, Menu& menu) : Window_(window),
		Map_(map), Menu_(menu), Event_(), Controls_(Camera_, *this),
		ButtonSelected_(nullptr), Quit_(false), TextInputSelected_(nullptr),
		AnimalSelected_(nullptr), Speed_(1.f), MainMenuHidden_(false),
		PlantGeneration_(500), TimeElapsedPlant_(0) {
		Settings::loadFonts();
		addMapBorder();
		resetCamera();
	}

	inline Window& getWindow() { return Window_; }
	inline Map& getMap() { return Map_; }
	inline Menu& getMenu() { return Menu_; }
	inline Camera& getCamera() { return Camera_; }
	float& getSpeed() { return Speed_; }
	void updateMap();
	void zoomIn();
	void zoomOut();
	void speedUp();
	void speedDown();
	void generatePlant(long long milliseconds);
	void moveCamera(float x, float y);
	void moveCamera(FPoint offset);
	void stopMoveCamera();
	void launch();
	bool addMapObject(std::unique_ptr<Drawable>& map_object);
	void removeSelectedAnimal();
	void highlightSelectedAnimal();
	void bindAnimalStatistics(Animal& animal);
	void toggleMainMenu();
	void hideMainMenu();
	void showMainMenu();
	void hideAnimalMenu();
	void showAnimalMenu();
	void select(Button& button);
	void select(TextInput& input);
	void select(Animal& animal);
	void unselect(Button& button);
	void unselect(TextInput& input);
	void unselect(Animal& animal);
	void unselectAll();

	friend Controls;
};
