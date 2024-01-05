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
#include <SDL2/SDL.h>
#include "Drawable.h"
#include "Camera.h"
#include "PointBase.hpp"
#include "Map.h"

class Window {
private:
	/* A handle to window */
	SDL_Window* Window_;
	/* A handle to renderer surface */
	SDL_Renderer* Renderer_;
	/* A base size of window in pixels / pixels
	   It is almost constant value and do not represent actual
	   window size */
	FPoint Size_;
	/* A list of menu elements(overlay targets) */
	std::vector<std::unique_ptr<Drawable>> MenuElements_;
	/* A scale of current window meaning:
	   <actual window size> =  Scale_ * Size_ */
	FPoint Scale_;
	std::unique_ptr<Drawable> Border_;

public:
	Window(float width, float height) : Window_(nullptr), Renderer_(nullptr),
		Size_(width, height), Scale_(1.f, 1.f) {}

	~Window() {
		if (Renderer_)
			SDL_DestroyRenderer(Renderer_);
		if (Window_)
			SDL_DestroyWindow(Window_);
	}

	FPoint getWindowSize() const;
	void setWindowSize(int width, int height);
	void setWindowSize(FPoint size);
	void scaleWindow(float width, float height);
	void scaleWindow(FPoint scale);
	bool createWindow(const char* title);
	void addMenuElement(std::unique_ptr<Drawable>& drawable);
	void setBorder(std::unique_ptr<Drawable>& border);
	void render(Map& map, Camera& camera);

	operator SDL_Renderer* () { return Renderer_; }
	operator SDL_Window* () { return Window_; }
};
