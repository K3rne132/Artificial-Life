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
#include "Shape.h"

class EmptyRect : public Shape {
public:
	EmptyRect(SDL_FRect rect, SDL_Color color) : Shape(rect, color) {}

	virtual void draw(SDL_Renderer* renderer, FPoint offset) override {
		SDL_SetRenderDrawColor(renderer, Color_.r, Color_.g, Color_.b, Color_.a);
		SDL_FRect rect = Rect_;
		rect.x += offset.X;
		rect.y += offset.Y;
		SDL_RenderDrawRectF(renderer, &rect);
	}
};
