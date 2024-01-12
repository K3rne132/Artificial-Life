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
#include <iostream>
#include "Drawable.h"
#include "Colors.h"

class Map;

class Plant : public Drawable {
private:
	inline static SDL_Color Color = BLUE;
	inline static float SizeInPixels_ = 5.f;

public:
	inline static unsigned int Count = 0;

	Plant() { ++Count; }
	Plant(FPoint xy) : Drawable(xy) { ++Count; }
	~Plant() { --Count; }

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
	virtual bool isMouseOver(FPoint mouse_pos) const override { return false; }
};
