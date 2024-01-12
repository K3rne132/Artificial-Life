// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include <algorithm>
#include <stdexcept>
#include "Map.h"

bool Map::addObject(std::unique_ptr<Drawable>& map_object) {
	Objects_.push_back(std::move(map_object));
	return true;
}

DrawableVector::const_iterator Map::removeObject(Drawable& map_object) {
	auto it = std::find_if(Objects_.begin(), Objects_.end(),
		[&map_object](const std::unique_ptr<Drawable>& ptr) {
			return ptr.get() == &map_object;
		});
	if (it != Objects_.end()) {
		return Objects_.erase(it);
	}
	return Objects_.end();
}

Drawable& Map::operator[](size_t index) const {
	if (index >= Objects_.size()) {
		throw std::out_of_range("Index out of bounds!");
	}
	return *Objects_[index].get();
}

Point Map::getMapSize() const {
	return Size_;
}

size_t Map::getSize() const { 
	return Objects_.size(); 
}
