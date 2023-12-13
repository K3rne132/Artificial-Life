#pragma once
#include "SDL.h"
#include "Window.h"
#include "PointBase.hpp"

class Controls {
private:
	bool _MiddleButtonPressed;
	FPoint _MouseBase, _MouseOffset;

	void getMousePos(FPoint& mouse);

public:
	Controls() : _MiddleButtonPressed(false), _MouseBase(0, 0), _MouseOffset(0, 0) {}

	void mouseButtonDown(int button);
	void mouseButtonUp(Window& window, int button);
	void mouseMotion(Window& window);
	void mouseWheel(Window& window, int y);
};