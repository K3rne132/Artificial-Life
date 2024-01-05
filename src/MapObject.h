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
#include "PointBase.hpp"
#include "Clickable.h"

class MapObject : public Clickable {
protected:
	Point Position_;

public:
	MapObject() : Position_(0, 0) {}
	MapObject(int x, int y) : Position_(x, y) {}

	void setPosition(Point position) {
		Position_ = position;
	}
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
};
