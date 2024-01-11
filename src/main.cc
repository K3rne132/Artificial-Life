// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include <iostream>
#include "Settings.h"
#include "Simulation.h"
#include "TextInput.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include <SDL_ttf.h>
#undef main

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}
	if (TTF_Init() != 0) {
		SDL_Quit();
		return 1;
	}
	if (!Settings::loadFonts()) {
		std::cerr << "Could not load fonts!";
		return 1;
	}
	Window window(1280, 720);
	if (!window.createWindow("Artificial Life Simulation")) {
		std::cerr << "Could not create window or renderer!";
		return 1;
	}

    Map map(3000, 3000);
	Menu menu;
	Simulation simulation(window, map, menu);

    auto anim1 = std::unique_ptr<Drawable>(new Carnivore(FPoint(100, 200), simulation));
    map.addObject(anim1);
    auto anim2 = std::unique_ptr<Drawable>(new Herbivore(FPoint(400, 600), simulation));
    map.addObject(anim2);

    auto elem1 = std::unique_ptr<Button>(
		new Button(FPoint(100.f, 100.f), FPoint(100.f, 100.f), BLUE, simulation));
	auto elem2 = std::unique_ptr<Button>(
		new TextInput(FPoint(100.f, 200.f), simulation, "random text input"));
    menu.addMainMenuElement(elem1);
    menu.addMainMenuElement(elem2);
	
	simulation.launch();

	SDL_Quit();
}