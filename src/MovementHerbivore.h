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
#include "Movement.h"

class MovementHerbivore : public Movement {
private:
	bool goEat(Nearest& n, Animal& animal);
	bool goRun(Nearest& n, Animal& animal);

public:
	virtual float move(Map& map, Animal& animal, float time_scale) override;
};
