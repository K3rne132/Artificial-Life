#pragma once
#include "Window.h"
#include "SDL.h"
#include "basePoint.hpp"
using Point = basePoint<int>;

class Simulation {
private:
	Window& _Window;
	SDL_Event _Event;
	bool _Quit;
	bool _MiddleButtonPressed;
	Point _BasePoint, _Point;

	void dispatchEvent();

public:
	Simulation(Window& window) : _Window(window), _Event(), _Quit(false),
		_MiddleButtonPressed(false), _BasePoint(0, 0), _Point(0, 0) {}
	void launch();
};