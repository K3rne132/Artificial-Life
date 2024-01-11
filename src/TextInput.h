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
#include <string>
#include "Text.h"
#include "Settings.h"
#include "Simulation.h"

class TextInput : public Text {
private:
	static const char PROMPT = '_';
	bool Selected_;
	std::string ModableText_;
	void updateText() {
		std::string printed;
		if (Selected_)
			printed = (ModableText_ + PROMPT);
		else
			printed = ModableText_;
		makeText(Settings::FontMain, printed, Parent_.getWindow());
	}

public:
	TextInput(FPoint xy, Simulation& parent, const char* text = nullptr,
		SDL_Color color = BLACK) : Text(xy, parent, text, color),
		Selected_(false) {
		if (text)
			ModableText_ = text;
	}
	~TextInput() {
		Parent_.unselect(*this);
	}

	void deleteLetter() {
		if (ModableText_.length() > 0) {
			ModableText_ = ModableText_.substr(0, ModableText_.length() - 1);
			updateText();
		}
	}

	void appLetters(const char* letters) {
		ModableText_ += letters;
		updateText();
	}

	std::string getInput() { return ModableText_; }

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override {
		Text::draw(renderer, offset);
		//
	}

	virtual bool isMouseOver(FPoint mouse_pos) const override {
		return Drawable::isMouseOver(mouse_pos);
	}

	virtual SDL_SystemCursor getCursorMouseOver() override {
		return SDL_SystemCursor::SDL_SYSTEM_CURSOR_IBEAM;
	}

	virtual void click() {
		Parent_.select(*this);
	}

	virtual void whenSelected() override {
		Selected_ = true;
		updateText();
	}

	virtual void whenUnselected() override {
		Selected_ = false;
		updateText();
	}
};
