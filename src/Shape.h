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
#include "Drawable.h"

class Shape : public Drawable {
protected:
	SDL_FRect Rect_;
	SDL_Color Color_;

public:
	Shape() : Rect_(SDL_FRect()), Color_(SDL_Color()) {}
	Shape(SDL_FRect rect, SDL_Color color) : Rect_(rect), Color_(color) {}

	virtual void click() override {}
};
