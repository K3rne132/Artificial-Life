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
	void setColor(SDL_Color color) {
		Color_ = color;
	}
	void setSize(FPoint size) {
		Size_ = size;
	}
	FPoint  getSize() const {
		return Size_;
	}
	void setPosition(FPoint position) {
		Position_ = position;
	}
	FPoint getPosition() const {
		return Position_;
	}
	virtual bool isMouseOver(FPoint mouse_pos) const;
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint());
	virtual SDL_SystemCursor getCursorMouseOver() {
		return SDL_SystemCursor::SDL_SYSTEM_CURSOR_HAND;
	}
	virtual void click() {}
	virtual void whenSelected() {}
	virtual void whenUnselected() {}
};
