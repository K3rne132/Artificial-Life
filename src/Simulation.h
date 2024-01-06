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
#include "Window.h"
#include "Map.h"
#include "SimulationSettings.h"
#include "Controls.h"
#include "Menu.h"

class Simulation {
private:
	Window& Window_;
	SimulationSettings Settings_;
	Map& Map_;
	SDL_Event Event_;
	Camera Camera_;
	Controls Controls_;
	Menu& Menu_;
	bool Quit_;

	void dispatchEvent();
	void addMapBorder();
	void resetCamera();

public:
	Simulation(Window& window, Map& map, Menu& menu) : Window_(window), Map_(map),
		Menu_(menu), Event_(), Quit_(false), Controls_(Camera_) {
		addMapBorder();
		resetCamera();
	}

	void zoomIn();
	void zoomOut();
	void moveCamera(float x, float y);
	void moveCamera(FPoint offset);
	void stopMoveCamera();
	void launch();
};
