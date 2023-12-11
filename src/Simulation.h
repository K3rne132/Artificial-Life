#pragma once
#include "Window.h"
#include "SDL.h"

class Simulation {
private:
	Window& _Window;
	SDL_Event _Event;
	bool _Quit;
	bool _MiddleButtonPressed;
	int _BaseX, _BaseY, _X, _Y;

	void dispatchEvent();

public:
	Simulation(Window& window) : _Window(window), _Event(), _Quit(false),
		_MiddleButtonPressed(false), _BaseX(0), _BaseY(0), _X(0), _Y(0) {}
	void launch();
};