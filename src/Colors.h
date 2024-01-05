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

static SDL_Color makeColor(int r, int g, int b, int a) {
	SDL_Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = a;
	return result;
}

#define WHITE makeColor(255, 255, 255, 255)
#define BLACK makeColor(0, 0, 0, 255)
#define RED makeColor(255, 0, 0, 255)
#define GREEN makeColor(0, 255, 0, 255)
#define BLUE makeColor(0, 0, 255, 255)
