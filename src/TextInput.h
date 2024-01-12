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
#include "EmptyRect.h"

class TextInput : public Text {
private:
	static const char PROMPT = '_';
	static const int MIN_WIDTH = 300.f;
	static const int MIN_HEIGHT = 30.f;

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
	FPoint getMinSize() const {
		FPoint min = FPoint(MIN_WIDTH, MIN_HEIGHT);
		if (Size_.X > min.X)
			min.X = Size_.X;
		if (Size_.Y > min.Y)
			min.Y = Size_.Y;
		return min;
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
		SDL_FRect rect;
		rect.x = Position_.X;
		rect.y = Position_.Y;
		FPoint min = getMinSize();
		rect.w = min.X;
		rect.h = min.Y;
		EmptyRect border(rect, BLACK);
		border.draw(renderer, offset);
	}

	virtual bool isMouseOver(FPoint mouse_pos) const override {
		return mouse_pos >= Position_ && mouse_pos <= Position_ + getMinSize();
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
