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
#include "Simulation.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "Window.h"
#include "Random.h"

#undef main

enum class Command {
	HELP,
	RANDOM,
	READ_FILE,
	SET_PARAMS
};

// Prints a help page
void printHelp() {
	std::cout << "Artificial Life Simulation\n"
		"Opcje:\n"
		"\t <> - uruchamia program z wartosciami losowymi\n"
		"\t -f <nazwa_pliku> - wczytuje mape z pliku json\n"
		"\t <miesozercy> <roslinozercy> <rosliny> <szerokosc_mapy> <wysokosc_mapy>\n"
		"\t\t- przypisuje kolejne wartosci do generatora mapy\n";
}

// Checks arguments from command line and then assigns tasks
Command parseInput(int argc, char** argv) {
	if (argc == 1)
		return Command::RANDOM;
	if (argc == 3) {
		if (!strcmp(argv[1], "-f")) {
			return Command::READ_FILE;
		}
	}
	if (argc == 6) {
		for (int i = 1; i < 6; ++i) {
			if (!std::atoi(argv[i])) {
				std::cerr << "Wartosci musza byc liczba calkowita wieksza od 0\n";
				return Command::HELP;
			}
		}
		return Command::SET_PARAMS;
	}
	return Command::HELP;
}

int main(int argc, char** argv) {
	Command cmd = parseInput(argc, argv);
	if (cmd == Command::HELP) {
		printHelp();
		return 1;
	}
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

    Map map;
	Menu menu;
	Simulation simulation(window, map, menu);
	switch (cmd) {
	case Command::RANDOM:
		if (!map.generate(
			getRandomInt(10, 100),
			getRandomInt(10, 100),
			getRandomInt(10, 100),
			1000, 1000, simulation))
			return 1;
		break;
	case Command::SET_PARAMS:
		if (!map.generate(
			std::atoi(argv[1]),
			std::atoi(argv[2]),
			std::atoi(argv[3]),
			std::atoi(argv[4]),
			std::atoi(argv[5]),
			simulation))
			return 1;
		break;
	case Command::READ_FILE:
		if (!map.readFromFile(argv[2], simulation))
			return 1;
		break;
	default:
		printHelp();
		return 1;
	}
	
	
	menu.createMainInterface(simulation);
	menu.createAnimalInterface(simulation);

	simulation.launch();

	SDL_Quit();
}
