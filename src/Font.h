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
#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

class Font {
private:
	TTF_Font* Font_;

public:
	Font() : Font_(nullptr) {}
	~Font() {
		if (Font_)
			TTF_CloseFont(Font_);
	}

	// Loads font from file with specified font size
	bool load(const char* path, int size) {
		Font_ = TTF_OpenFont(path, size);
		if (!Font_)
			return false;
		return true;
	}

	operator TTF_Font*() {
		return Font_;
	}

	operator bool() {
		return Font_;
	}
};
