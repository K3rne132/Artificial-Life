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
#include <SDL2/SDL.h>
#include "PointBase.hpp"
#include "Camera.h"
#include "Map.h"
#include "Menu.h"
#include "Drawable.h"

class Simulation;

class Controls {
private:
	bool MiddleButtonPressed_;
	FPoint MouseBase_, MouseOffset_;
	Camera& Camera_;
	Drawable* MouseOver_;

	FPoint getMousePos();
	FPoint getRelativeMousePos();
	void storeMousePos(FPoint& mouse);

public:
	Controls(Camera& camera) : Camera_(camera), MouseOver_(nullptr),
		MiddleButtonPressed_(false), MouseBase_(0, 0), MouseOffset_(0, 0) {}

	void mouseButtonDown(int button);
	void mouseButtonUp(Simulation& simulation, int button);
	void mouseMotion(Simulation& simulation);
	void mouseWheel(Simulation& simulation, int y);
	bool isMouseOver(Menu& menu, Map& map);
};
