#include <iostream>
#include "Simulation.h"

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}
	Window window(1280, 720);
	if (!window.createWindow("Artificial Life Simulation")) {
		std::cerr << "Could not create window or renderer!";
		return 1;
	}

	SDL_FRect rect = { 100, 100, 100, 100 };
	SDL_Color color = { 127, 80, 180, 255 };
	window.addTarget(std::unique_ptr<Drawable>(new Drawable(rect, color)));
	rect = { 500, 400, 100, 100 };
	color = { 80, 180, 127, 255 };
	window.addTarget(std::unique_ptr<Drawable>(new Drawable(rect, color)));
	rect = { 600, 200, 200, 200 };
	color = { 180, 80, 127, 255 };
	window.addMenuElement(std::unique_ptr<Drawable>(new Drawable(rect, color)));

	Simulation simulation(window);
	simulation.launch();

	SDL_Quit();
}