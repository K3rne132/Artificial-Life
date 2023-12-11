#include "Simulation.h"

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
		if (_Event.wheel.y > 0)
			_Window.zoomIn();
		if (_Event.wheel.y < 0)
			_Window.zoomOut();
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (_Event.button.button == SDL_BUTTON_MIDDLE) {
			if (!_MiddleButtonPressed) {
				_MiddleButtonPressed = true;
				SDL_GetMouseState(&_BaseX, &_BaseY);
			}
		}
		break;
	case SDL_MOUSEMOTION:
		if (_MiddleButtonPressed) {
			SDL_GetMouseState(&_X, &_Y);
			_Window.moveCamera(_BaseX - _X, _BaseY - _Y);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (_Event.button.button == SDL_BUTTON_MIDDLE) {
			_MiddleButtonPressed = false;
			_Window.stopMoveCamera();
		}
		break;
	}
}

void Simulation::launch() {
	while (!_Quit) {
		while (SDL_PollEvent(&_Event)) {
			dispatchEvent();
			_Window.render();
		}
		SDL_Delay(16); // 60fps
	}
}