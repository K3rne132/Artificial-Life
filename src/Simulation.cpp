#include "Simulation.h"
#include "EmptyRect.h"

void Simulation::dispatchEvent() {
	switch (_Event.type) {
	case SDL_QUIT:
		_Quit = true;
		break;
	case SDL_WINDOWEVENT:
		if (_Event.window.event == SDL_WINDOWEVENT_RESIZED) {
			_Window.scaleWindow(_Event.window.data1, _Event.window.data2);
		}
		break;
	case SDL_MOUSEWHEEL:
		_Controls.mouseWheel(_Window, _Event.wheel.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		_Controls.mouseButtonDown(_Event.button.button);
		break;
	case SDL_MOUSEMOTION:
		_Controls.mouseMotion(_Window);
		break;
	case SDL_MOUSEBUTTONUP:
		_Controls.mouseButtonUp(_Window, _Event.button.button);
		break;
	}
}

void Simulation::addMapBorder() {
	SDL_FRect dest = {};
	dest.w = _Map.getMapSize().X;
	dest.h = _Map.getMapSize().Y;
	auto border = std::unique_ptr<Drawable>(new EmptyRect(dest, SDL_Color()));
	_Window.setBorder(border);
}

void Simulation::resetCamera() {
	_Window.resetCamera(_Map.getMapSize());
}

void Simulation::launch() {
	while (!_Quit) {
		while (SDL_PollEvent(&_Event)) {
			dispatchEvent();
			_Window.render(_Map);
		}
		SDL_Delay(16); // 60fps
	}
}