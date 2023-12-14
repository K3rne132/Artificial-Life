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
		if (!MiddleButtonPressed_) {
			MiddleButtonPressed_ = true;
			getMousePos(MouseBase_);
		}
		break;
	}
}

void Controls::mouseButtonUp(Window& window, int button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		MiddleButtonPressed_ = false;
		window.stopMoveCamera();
	}
}

void Controls::mouseMotion(Window& window) {
	if (MiddleButtonPressed_) {
		getMousePos(MouseOffset_);
		FPoint asd = MouseBase_ + MouseOffset_;
		window.moveCamera(MouseBase_ - MouseOffset_);
		window.moveCamera(MouseBase_ - MouseOffset_);
	}
}

void Controls::mouseWheel(Window& window, int y) {
	if (y > 0)
		window.zoomIn();
	else if (y < 0)
		window.zoomOut();
}