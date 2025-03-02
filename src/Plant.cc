// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.


#include "Plant.h"


void Plant::draw(SDL_Renderer* renderer, FPoint offset) {
	SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
	SDL_FRect rect;
	rect.x = offset.X + Position_.X;
	rect.y = offset.Y + Position_.Y;
	rect.w = SIZE;
	rect.h = SIZE;
	SDL_RenderFillRectF(renderer, &rect);
}
