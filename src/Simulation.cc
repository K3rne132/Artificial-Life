// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Simulation.h"
#include "FilledRect.h"
#include "Colors.h"

void Simulation::dispatchEvent() {
	switch (Event_.type) {
	case SDL_QUIT:
		Quit_ = true;
		break;
	case SDL_WINDOWEVENT:
		if (Event_.window.event == SDL_WINDOWEVENT_RESIZED) {
			Window_.scaleWindow(Event_.window.data1, Event_.window.data2);
		}
		break;
	case SDL_MOUSEWHEEL:
		Controls_.mouseWheel(*this, Event_.wheel.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		Controls_.mouseButtonDown(Event_.button.button);
		break;
	case SDL_MOUSEMOTION:
		Controls_.mouseMotion(*this);
		break;
	case SDL_MOUSEBUTTONUP:
		Controls_.mouseButtonUp(*this, Event_.button.button);
		break;
	}
}

void Simulation::addMapBorder() {
	SDL_FRect dest = {};
	dest.w = Map_.getMapSize().X;
	dest.h = Map_.getMapSize().Y;
	auto border = std::unique_ptr<Drawable>(new FilledRect(dest, WHITE));
	Window_.setBorder(border);
}

void Simulation::resetCamera() {
	Camera_.setMapSize(Map_.getMapSize());
	Camera_.setCameraSize(Window_.getWindowSize());
}

void Simulation::zoomIn() {
	Camera_.setZoom(Camera_.getZoom() * 1.15f);
}

void Simulation::zoomOut() {
	Camera_.setZoom(Camera_.getZoom() * 0.9f);
}

void Simulation::moveCamera(float x, float y) {
	moveCamera(FPoint(x, y));
}

void Simulation::moveCamera(FPoint offset) {
	Camera_.setOffset(offset);
}

void Simulation::stopMoveCamera() {
	Camera_.storeOffset();
}

void Simulation::launch() {
	while (!Quit_) {
		while (SDL_PollEvent(&Event_)) {
			dispatchEvent();
			Window_.render(Map_, Camera_);
		}
		SDL_Delay(16); // 60fps
	}
}
