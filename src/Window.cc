// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Window.h"
#include "Menu.h"

FPoint Window::getWindowSize() const {
	return Size_;
}

void Window::setWindowSize(int width, int height) {
	Size_.X = width;
	Size_.Y = height;
	if (Window_)
		SDL_SetWindowSize(Window_, width, height);
}

void Window::setWindowSize(FPoint size) {
	setWindowSize(size.X, size.Y);
}

void Window::scaleWindow(float width, float height) {
	Scale_.X = width / Size_.X;
	Scale_.Y = height / Size_.Y;
	SDL_RenderSetScale(Renderer_, Scale_.X, Scale_.Y);
}

void Window::scaleWindow(FPoint scale) {
	scaleWindow(scale.X, scale.Y);
}

bool Window::createWindow(const char* title) {
	Window_ = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Size_.X,
		Size_.Y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	if (!Window_)
		return false;
	Renderer_ = SDL_CreateRenderer(
		Window_,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (!Renderer_) {
		SDL_DestroyWindow(Window_);
		return false;
	}
	return true;
}

void Window::setBorder(std::unique_ptr<Drawable>& border) {
	Border_ = std::move(border);
}

void Window::render(Map& map, Menu& menu, Camera& camera) {
	SDL_SetRenderDrawColor(Renderer_, 0, 0, 0, 255);
	SDL_RenderClear(Renderer_);
	SDL_RenderSetScale(Renderer_,
		Scale_.X * camera.getZoom(),
		Scale_.Y * camera.getZoom());
	if (Border_)
		Border_->draw(Renderer_, !camera.getOffset());
	for (const auto& object : map)
		object->draw(Renderer_, !camera.getOffset());
	SDL_RenderSetScale(Renderer_, Scale_.X, Scale_.Y);
	for (const auto& element : menu) {
		if (!element->isHidden())
			element->draw(Renderer_);
	}
	SDL_RenderPresent(Renderer_);
}
