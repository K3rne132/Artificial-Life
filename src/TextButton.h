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
#include <functional>
#include "Text.h"
#include "EmptyRect.h"
#include "FilledRect.h"

class TextButton : public Text {
private:
	FPoint ButtonSize_;
	std::function<void()> Lambda_;

public:
	TextButton(FPoint xy, FPoint size, Simulation& parent, const char* text,
		std::function<void()> lambda, SDL_Color color = BLACK) : Lambda_(lambda),
		Text(xy, parent, text, color),
		ButtonSize_(size) {
		if (text)
			makeText(Settings::FontMain, text, parent.getWindow());
	}

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override {
		SDL_FRect rect;
		rect.x = Position_.X;
		rect.y = Position_.Y;
		rect.w = ButtonSize_.X;
		rect.h = ButtonSize_.Y;
		FilledRect backgroud(rect, ECRU);
		backgroud.draw(renderer, offset);
		EmptyRect border(rect, BLACK);
		border.draw(renderer, offset);
		Text::draw(renderer, offset);
	}

	virtual bool isMouseOver(FPoint mouse_pos) const override {
		return mouse_pos >= Position_ && mouse_pos <= Position_ + ButtonSize_;
	}

	virtual SDL_SystemCursor getCursorMouseOver() override {
		return SDL_SystemCursor::SDL_SYSTEM_CURSOR_HAND;
	}

	virtual void click() override {
		Lambda_();
	}
};
