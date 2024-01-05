// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Controls.h"
#include "Simulation.h"

FPoint Controls::getMousePos() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	FPoint result;
	result.X = static_cast<float>(x);
	result.Y = static_cast<float>(y);
	return result;
}

FPoint Controls::getRelativeMousePos() {
	FPoint result = getMousePos();
	result /= Camera_.getZoom();
	result += Camera_.getOffset();
	return result;
}

void Controls::storeMousePos(FPoint& mouse) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	mouse.X = static_cast<float>(x);
	mouse.Y = static_cast<float>(y);
}

void Controls::mouseButtonDown(int button) {
	switch (button) {
	case SDL_BUTTON_MIDDLE:
		if (!MiddleButtonPressed_) {
			MiddleButtonPressed_ = true;
			storeMousePos(MouseBase_);
		}
		break;
	}
}

void Controls::mouseButtonUp(Simulation& simulation, int button) {
	switch (button) {
	case SDL_BUTTON_MIDDLE:
		MiddleButtonPressed_ = false;
		simulation.stopMoveCamera();
	}
}

void Controls::mouseMotion(Simulation& simulation) {
	std::cout << getMousePos() << "\n";
	std::cout << getRelativeMousePos() << "\n";
	if (MiddleButtonPressed_) {
		storeMousePos(MouseOffset_);
		FPoint asd = MouseBase_ + MouseOffset_;
		simulation.moveCamera(MouseBase_ - MouseOffset_);
		simulation.moveCamera(MouseBase_ - MouseOffset_);
	}
}

void Controls::mouseWheel(Simulation& simulation, int y) {
	if (y > 0)
		simulation.zoomIn();
	else if (y < 0)
		simulation.zoomOut();
}
