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

class Map;
class Drawable;
class Menu;
class Simulation;

class Controls {
private:
	bool MiddleButtonPressed_;
	FPoint MouseBase_, MouseOffset_;
	Camera& Camera_;
	Drawable* MouseOver_;
	SDL_SystemCursor CurrentCursor_;
	SDL_Cursor* Cursor_;
	Simulation& Parent_;

	FPoint getMousePos();
	FPoint getRelativeMousePos();
	void storeMousePos(FPoint& mouse);

public:
	Controls(Camera& camera, Simulation& parent) : Camera_(camera),
		MouseOver_(nullptr), Cursor_(nullptr), MiddleButtonPressed_(false),
		MouseBase_(0, 0), MouseOffset_(0, 0), Parent_(parent),
		CurrentCursor_(SDL_SYSTEM_CURSOR_ARROW) {}

	void mouseButtonDown(int button);
	void mouseButtonUp(int button);
	void mouseMotion();
	void mouseWheel(int y);
	void keyPressed(int key);
	void textInput(const char* letters);
	void setSystemCursor(SDL_SystemCursor type = SDL_SYSTEM_CURSOR_ARROW);
	void updateCursor();
	bool isMouseOver(Menu& menu, Map& map);
};
