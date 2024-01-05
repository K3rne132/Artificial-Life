// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "MapObject.h"

void MapObject::draw(SDL_Renderer* renderer, FPoint offset) {
	SDL_SetRenderDrawColor(renderer, Color_.r, Color_.g, Color_.b, Color_.a);
	SDL_FRect rect;
	rect.x = offset.X + Position_.X;
	rect.y = offset.Y + Position_.Y;
	rect.w = Size_.X;
	rect.h = Size_.Y;
	SDL_RenderFillRectF(renderer, &rect);
}
