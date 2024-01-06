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

class Menu {
private:
	std::vector<std::unique_ptr<Drawable>> MenuElements_;

public:
	void addMenuElement(std::unique_ptr<Drawable>& menu_obj) {
		MenuElements_.push_back(std::move(menu_obj));
	}
	inline auto begin() const { return MenuElements_.begin(); }
	inline auto end() const { return MenuElements_.end(); }
};
