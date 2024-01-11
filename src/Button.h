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
#include "Drawable.h"
#include "Colors.h"

class Simulation;

enum class ButtonGroup {
	NONE,
	MAINMENU,
	CONTEXTMENU
};

class Button : public Drawable {
protected:
	Simulation& Parent_;
	ButtonGroup Group_;
	bool Hidden_;

public:
	Button(FPoint xy, FPoint size, SDL_Color color, Simulation& parent) :
		Drawable(xy), Parent_(parent), Hidden_(false), Group_(ButtonGroup::NONE) {
		setSize(size);
		setColor(color);
	}

	ButtonGroup getGroup() { return Group_; }
	void setGroup(ButtonGroup group) { Group_ = group; }
	bool isHidden() const { return Hidden_; }
	void hide() { Hidden_ = true; }
	void show() { Hidden_ = false; }
	virtual void click() override { std::cout << "BUTTON CLICKED!\n"; }
};
