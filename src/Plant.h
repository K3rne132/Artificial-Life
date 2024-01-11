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

class Plant : Drawable {
private:
	float NutritionalValue_;

public:
	Plant() : NutritionalValue_(0.f) {}
	Plant(float nutritional_value) : NutritionalValue_(nutritional_value) {}

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
	virtual bool isMouseOver(FPoint mouse_pos) const override { return false; }
};
