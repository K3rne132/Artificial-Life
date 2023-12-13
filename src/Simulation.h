#pragma once
#include "Window.h"
#include "Map.h"
#include "SimulationSettings.h"
#include "Controls.h"

class Simulation {
private:
	Window& _Window;
	SimulationSettings _Settings;
	Map& _Map;
	SDL_Event _Event;
	Controls _Controls;
	bool _Quit;

	void dispatchEvent();
	void addMapBorder();
	void resetCamera();

public:
	Simulation(Window& window, Map& map) : _Window(window), _Map(map),
		_Event(), _Quit(false) {
		addMapBorder();
		resetCamera();
	}
	void launch();
};