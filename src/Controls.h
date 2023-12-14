#pragma once
#include <SDL2/SDL.h>
#include "Window.h"
#include "PointBase.hpp"

class Controls {
private:
	bool MiddleButtonPressed_;
	FPoint MouseBase_, MouseOffset_;

	void getMousePos(FPoint& mouse);

public:
	Controls() : MiddleButtonPressed_(false), MouseBase_(0, 0), MouseOffset_(0, 0) {}

	void mouseButtonDown(int button);
	void mouseButtonUp(Window& window, int button);
	void mouseMotion(Window& window);
	void mouseWheel(Window& window, int y);
};