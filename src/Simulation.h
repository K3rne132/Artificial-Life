#pragma once
#include "Window.h"
#include "Map.h"
#include "SimulationSettings.h"
#include "Controls.h"

class Simulation {
private:
	Window& Window_;
	SimulationSettings Settings_;
	Map& Map_;
	SDL_Event Event_;
	Controls Controls_;
	bool Quit_;

	void dispatchEvent();
	void addMapBorder();
	void resetCamera();

public:
	Simulation(Window& window, Map& map) : Window_(window), Map_(map),
		Event_(), Quit_(false) {
		addMapBorder();
		resetCamera();
	}
	void launch();
};