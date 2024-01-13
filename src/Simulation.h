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
#include "Settings.h"

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
		PlantGeneration_(100), TimeElapsedPlant_(0) {
		Settings::loadFonts();
		addMapBorder();
		resetCamera();
	}

	// Returns handle to Window
	inline Window& getWindow() { return Window_; }
	// Returns handle to Map
	inline Map& getMap() { return Map_; }
	// Returns handle to Menu
	inline Menu& getMenu() { return Menu_; }
	// Returns handle to Camera
	inline Camera& getCamera() { return Camera_; }
	// Returns reference to simulation speed
	float& getSpeed() { return Speed_; }
	/*
	* Adds border depending on new map size and resets camera
	* to point to the map origin
	*/
	void updateMap();
	// Zoom in by camera
	void zoomIn();
	// Zoom out by camera
	void zoomOut();
	// Speeds up the simulation to 10.f
	void speedUp();
	// Slows down the simulation to 0.f
	void speedDown();
	/*
	* Generates new plant in random place after PlantGeneration_ time
	* (milliseconds are aggregating)
	*/
	void generatePlant(long long milliseconds);
	// Moves camera by offset
	void moveCamera(float x, float y);
	// Moves camera by offset
	void moveCamera(FPoint offset);
	// Stop moving camera (store offset after shifting map)
	void stopMoveCamera();
	// Launch simulation
	void launch();
	// Adds object to map
	bool addMapObject(std::unique_ptr<Drawable>& map_object);
	// Delete selected animal (performed by button)
	void removeSelectedAnimal();
	// Highlight selected animal by drawing border around object
	void highlightSelectedAnimal();
	// Binds animal statistics to be shown
	void bindAnimalStatistics(Animal& animal);
	// Shows/hides main menu
	void toggleMainMenu();
	// Hides main menu
	void hideMainMenu();
	// Shows main menu
	void showMainMenu();
	// Hides animal menu
	void hideAnimalMenu();
	// Shows animal menu
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
