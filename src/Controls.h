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

	// Do actions when one of mouse buttons (button) is pressed
	void mouseButtonDown(int button);
	// Do actions when one of mouse buttons (button) is released
	void mouseButtonUp(int button);
	// Do actions when mouse is moving
	void mouseMotion();
	// Do actions when mouse scroll is triggered in y direction
	void mouseWheel(int y);
	// Do actions when one of keyboard keys is pressed
	void keyPressed(int key);
	// Do actions when text is typed from keyboard
	void textInput(const char* letters);
	// Updates cursor depending on type (arrow, hand, etc.)
	void setSystemCursor(SDL_SystemCursor type = SDL_SYSTEM_CURSOR_ARROW);
	// Checks if cursor is over MouseOver objects and sets system cursor
	void updateCursor();
	// Checks whether the cursor is over any object
	bool isMouseOver(Menu& menu, Map& map);
};
