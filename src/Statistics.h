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
#include "Trait.h"

class Statistics {
public:
	Trait Energy;
	Trait Speed;
	Trait Size;

	Statistics() : Energy(0.f, 100.f, 100.f),
		Speed(0.25f, 4.f, 1.f), Size(0.5f, 2.f, 1.f) {}
};
