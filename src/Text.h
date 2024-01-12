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
#include <SDL2/SDL.h>
#include "Button.h"
#include "Settings.h"
#include "Simulation.h"

class Text : public Button {
protected:
	SDL_Texture* Texture_;

public:
	Text(FPoint xy, Simulation& parent, const char* text = nullptr,
		SDL_Color color = BLACK) : Texture_(nullptr),
		Button(xy, FPoint(0, 0), color, parent) {}
	~Text() {
		SDL_DestroyTexture(Texture_);
	}

	// Create texture from given text (need to be drawn)
	bool makeText(Font& font, std::string text, SDL_Renderer* renderer);
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
	virtual bool isMouseOver(FPoint mouse_pos) const override { return false; }
	operator SDL_Texture*() { return Texture_; }
	operator bool() { return Texture_; }
};
