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

class Drawable {
protected:
	FPoint Size_;
	SDL_Color Color_;
	FPoint Position_;

public:
	Drawable() : Color_(SDL_Color()) {}
	Drawable(FPoint xy) : Position_(xy), Color_(SDL_Color()) {}
	virtual ~Drawable() {}

	// Sets main color
	void setColor(SDL_Color color) {
		Color_ = color;
	}
	// Return main color
	SDL_Color getColor() const {
		return Color_;
	}
	// Updates size
	void setSize(FPoint size) {
		Size_ = size;
	}
	// Return width and height
	FPoint  getSize() const {
		return Size_;
	}
	// Updated position
	void setPosition(FPoint position) {
		Position_ = position;
	}
	// Return top-left position
	FPoint getPosition() const {
		return Position_;
	}
	// Return center position
	virtual FPoint getCenter() const {
		return Position_ + Size_ / 2;
	}
	// Checks whether the cursor is over object
	virtual bool isMouseOver(FPoint mouse_pos) const;
	// Draws object (can be shifted by offset)
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint());
	// Return which system cursor will be displayed on hover
	virtual SDL_SystemCursor getCursorMouseOver() {
		return SDL_SystemCursor::SDL_SYSTEM_CURSOR_HAND;
	}
	// Perform actions when clicked
	virtual void click() {}
	// Perform actions when selected
	virtual void whenSelected() {}
	// Perform actions when unselected
	virtual void whenUnselected() {}
};
