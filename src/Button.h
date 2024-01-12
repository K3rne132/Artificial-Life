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
	ANIMALMENU
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

	// Return current assigned group of button
	ButtonGroup getGroup() { return Group_; }
	/*
	* Set group for button(all buttons in the same group
	* will be treated in the same way
	*/
	void setGroup(ButtonGroup group) { Group_ = group; }
	// Check whether button is rendered
	bool isHidden() const { return Hidden_; }
	// Mark to do not render button
	void hide() { Hidden_ = true; }
	// Mark to render button
	void show() { Hidden_ = false; }
};
