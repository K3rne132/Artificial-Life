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
#include "Menu.h"
#include "Map.h"
#include "Drawable.h"
#include "Simulation.h"
#include "TextInput.h"

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
	case SDL_BUTTON_LEFT:
		if (MouseOver_)
			MouseOver_->click();
		else
			Parent_.unselectAll();
		break;
	case SDL_BUTTON_RIGHT:
		Parent_.unselectAll();
		break;
	case SDL_BUTTON_MIDDLE:
		if (!MiddleButtonPressed_) {
			setSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
			MiddleButtonPressed_ = true;
			storeMousePos(MouseBase_);
		}
		break;
	}
}

void Controls::mouseButtonUp(int button) {
	switch (button) {
	case SDL_BUTTON_MIDDLE:
		MiddleButtonPressed_ = false;
		Parent_.stopMoveCamera();
	}
}

void Controls::mouseMotion() {
	if (MiddleButtonPressed_) {
		storeMousePos(MouseOffset_);
		FPoint asd = MouseBase_ + MouseOffset_;
		Parent_.moveCamera(MouseBase_ - MouseOffset_);
		Parent_.moveCamera(MouseBase_ - MouseOffset_);
	}
	else if (isMouseOver(Parent_.Menu_, Parent_.Map_)) {
		updateCursor();
	}
	else {
		setSystemCursor();
	}
}

void Controls::mouseWheel(int y) {
	if (y > 0)
		Parent_.zoomIn();
	else if (y < 0)
		Parent_.zoomOut();
}

void Controls::keyPressed(int key) {
	switch (key) {
		case SDLK_BACKSPACE:
			if (Parent_.TextInputSelected_)
				Parent_.TextInputSelected_->deleteLetter();
	}
}

void Controls::textInput(const char* letter) {
	if (Parent_.TextInputSelected_)
		Parent_.TextInputSelected_->appLetters(letter);
}

bool Controls::isMouseOver(Menu& menu, Map& map) {
	for (const auto& obj : menu) {
		if (!obj->isHidden() && obj->isMouseOver(getMousePos())) {
			MouseOver_ = obj.get();
			return true;
		}
	}
	auto it = map.rbegin();
	while (it != map.rend()) {
		if (it->get()->isMouseOver(getRelativeMousePos())) {
			MouseOver_ = it->get();
			return true;
		}
		it++;
	}
	//for (const auto& obj : map) {
	//	if (obj->isMouseOver(getRelativeMousePos())) {
	//		MouseOver_ = obj.get();
	//		return true;
	//	}
	//}
	MouseOver_ = nullptr;
	return false;
}

void Controls::setSystemCursor(SDL_SystemCursor type) {
	if (type == CurrentCursor_)
		return;
	SDL_Cursor* system = SDL_CreateSystemCursor(type);
	if (Cursor_)
		SDL_FreeCursor(Cursor_);
	Cursor_ = system;
	CurrentCursor_ = type;
	SDL_SetCursor(system);
}

void Controls::updateCursor() {
	if (MouseOver_)
		setSystemCursor(MouseOver_->getCursorMouseOver());
}
