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

void Window::drawBorder() {
	SDL_SetRenderDrawColor(Renderer_, 0, 0, 0, 255);
	int offsetx = Camera_.getOffset().X;
	int offsety = Camera_.getOffset().Y;
	SDL_Rect border = SDL_Rect{ -offsetx, -offsety, Size_.X, Size_.Y };
	SDL_RenderDrawRect(Renderer_, &border);
}

Point Window::getWindowSize() const {
	return Size_;
}

void Window::setWindowSize(int width, int height) {
	Size_.X = width;
	Size_.Y = height;
	if (Window_)
		SDL_SetWindowSize(Window_, width, height);
}

void Window::setWindowSize(Point size) {
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

void Window::zoomIn() {
	Camera_.setZoom(Camera_.getZoom() * 1.15f);
}

void Window::zoomOut() {
	Camera_.setZoom(Camera_.getZoom() * 0.9f);
}

void Window::moveCamera(float x, float y) {
	moveCamera(FPoint(x, y));
}

void Window::moveCamera(FPoint offset) {
	Camera_.setOffset(offset);
}

void Window::stopMoveCamera() {
	Camera_.storeOffset();
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
	if (Window_ == nullptr)
		return false;
	Renderer_ = SDL_CreateRenderer(
		Window_,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (Renderer_ == nullptr) {
		SDL_DestroyWindow(Window_);
		return false;
	}
	return true;
}

void Window::addMenuElement(std::unique_ptr<Drawable>& drawable) {
	MenuElements_.push_back(std::move(drawable));
}

void Window::setBorder(std::unique_ptr<Drawable>& border) {
	Border_ = std::move(border);
}

void Window::resetCamera(Point mapsize) {
	Camera_.setMapSize(mapsize);
}

void Window::render(Map& map) {
	SDL_SetRenderDrawColor(Renderer_, 255, 255, 255, 255);
	SDL_RenderClear(Renderer_);
	SDL_RenderSetScale(Renderer_,
		Scale_.X * Camera_.getZoom(),
		Scale_.Y * Camera_.getZoom());
	if (Border_)
		Border_->draw(Renderer_, !Camera_.getOffset());
	for (const auto& object : map)
		object->draw(Renderer_, !Camera_.getOffset());
	SDL_RenderSetScale(Renderer_, Scale_.X, Scale_.Y);
	for (const auto& element : MenuElements_)
		element->draw(Renderer_);
	SDL_RenderPresent(Renderer_);
}
