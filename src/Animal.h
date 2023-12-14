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
#include <memory>
#include "MapObject.h"
#include "Statistics.h"
#include "Movement.h"

class Animal : public MapObject {
private:
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;

public:
	Animal() {}
	Animal(int x, int y) : MapObject(x, y) {}

	bool isMoving() const;
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
};
