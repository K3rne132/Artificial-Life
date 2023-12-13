#include "Controls.h"

void Controls::getMousePos(FPoint& mouse) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	mouse.X = static_cast<float>(x);
	mouse.Y = static_cast<float>(y);
}

void Controls::mouseButtonDown(int button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		if (!_MiddleButtonPressed) {
			_MiddleButtonPressed = true;
			getMousePos(_MouseBase);
		}
		break;
	}
}

void Controls::mouseButtonUp(Window& window, int button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		_MiddleButtonPressed = false;
		window.stopMoveCamera();
	}
}

void Controls::mouseMotion(Window& window) {
	if (_MiddleButtonPressed) {
		getMousePos(_MouseOffset);
		FPoint asd = _MouseBase + _MouseOffset;
		window.moveCamera(_MouseBase - _MouseOffset);
		window.moveCamera(_MouseBase - _MouseOffset);
	}
}

void Controls::mouseWheel(Window& window, int y) {
	if (y > 0)
		window.zoomIn();
	else if (y < 0)
		window.zoomOut();
}