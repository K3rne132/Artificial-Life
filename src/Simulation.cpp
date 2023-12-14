#include "Simulation.h"
#include "EmptyRect.h"

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
		Controls_.mouseWheel(Window_, Event_.wheel.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		Controls_.mouseButtonDown(Event_.button.button);
		break;
	case SDL_MOUSEMOTION:
		Controls_.mouseMotion(Window_);
		break;
	case SDL_MOUSEBUTTONUP:
		Controls_.mouseButtonUp(Window_, Event_.button.button);
		break;
	}
}

void Simulation::addMapBorder() {
	SDL_FRect dest = {};
	dest.w = Map_.getMapSize().X;
	dest.h = Map_.getMapSize().Y;
	auto border = std::unique_ptr<Drawable>(new EmptyRect(dest, SDL_Color()));
	Window_.setBorder(border);
}

void Simulation::resetCamera() {
	Window_.resetCamera(Map_.getMapSize());
}

void Simulation::launch() {
	while (!Quit_) {
		while (SDL_PollEvent(&Event_)) {
			dispatchEvent();
			Window_.render(Map_);
		}
		SDL_Delay(16); // 60fps
	}
}