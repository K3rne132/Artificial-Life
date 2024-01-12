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
#include <vector>
#include <memory>
#include "Drawable.h"

using DrawableVector = std::vector<std::unique_ptr<Drawable>>;

class Map {
private:
	Point Size_;
	DrawableVector Objects_;

public:
	Map() : Size_(0, 0) {}
	Map(int width, int height) : Size_(width, height) {}

	bool addObject(std::unique_ptr<Drawable>& map_object);
	DrawableVector::const_iterator removeObject(Drawable& map_object);
	inline auto begin() const { return Objects_.begin(); }
	inline auto end() const { return Objects_.end(); }
	Drawable& operator[](size_t index) const;
	Point getMapSize() const;
	size_t getSize() const;
};
