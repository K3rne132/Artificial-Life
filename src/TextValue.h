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
#include <sstream>
#include <iomanip>
#include "Text.h"
#include "Settings.h"
#include "Simulation.h"

template <typename T>
class TextValue : public Text {
private:
	const T* Value_;
	int Precision_;
	std::string Text_;

	void updateValue() {
		std::stringstream to_print;
		to_print << Text_;
		to_print << std::fixed << std::setprecision(Precision_) << *Value_;
		makeText(Settings::FontMain, to_print.str(), Parent_.getWindow());
	}

public:
	TextValue(FPoint xy, Simulation& parent, const char* text = nullptr,
		SDL_Color color = BLACK) : Precision_(2), Value_(nullptr),
		Text(xy, parent, text, color) {
		if (text)
			Text_ = text;
	}

	void bindValue(T* value, int precision = 2) {
		Value_ = value;
		updateValue();
	}

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override {
		if (Value_) {
			updateValue();
			Text::draw(renderer, offset);
		}
	}
};
