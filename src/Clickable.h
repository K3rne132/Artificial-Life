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
#include "Drawable.h"

class Clickable : public Drawable {
protected:
	FPoint Size_;
	SDL_Color Color_;

public:
	Clickable() : Size_(), Color_(SDL_Color()) {}

	void setColor(SDL_Color color) {
		Color_ = color;
	}

	void setSize(FPoint size) {
		Size_ = size;
	}
};