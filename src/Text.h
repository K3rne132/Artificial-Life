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
#include <SDL.h>
#include "Font.h"
#include "Window.h"
#include "Button.h"
#include "Colors.h"

class Text : public Button {
protected:
	SDL_Texture* Texture_;

public:
	Text(FPoint xy, Simulation& parent, const char* text = nullptr,
		SDL_Color color = BLACK) : Texture_(nullptr),
		Button(xy, FPoint(0, 0), color, parent) {
		if (text)
			makeText(Settings::FontMain, text, Parent_.getWindow());
	}
	~Text() {
		SDL_DestroyTexture(Texture_);
	}

	bool makeText(Font& font, std::string text, SDL_Renderer* renderer) {
		if (text.length() == 0) {
			SDL_DestroyTexture(Texture_);
			Texture_ = nullptr;
			return true;
		}
		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), Color_);
		if (!surface) {
			return false;
		}
		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!temp_texture) {
			SDL_FreeSurface(surface);
			return false;
		}
		SDL_DestroyTexture(Texture_);
		Texture_ = temp_texture;
		Size_.X = surface->w;
		Size_.Y = surface->h;
		SDL_FreeSurface(surface);
		return true;
	}

	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override {
		SDL_FRect rect;
		rect.x = Position_.X;
		rect.y = Position_.Y;
		rect.w = Size_.X;
		rect.h = Size_.Y;
		SDL_RenderCopyF(renderer, Texture_, NULL, &rect);
	}

	virtual bool isMouseOver(FPoint mouse_pos) const override {
		return false;
	}

	operator SDL_Texture*() {
		return Texture_;
	}

	operator bool() {
		return Texture_;
	}
};
