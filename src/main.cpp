#include <iostream>
#include "Simulation.h"
#include "FilledRect.h"
#include "Animal.h"
#undef main

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}
	Window window(1280, 720);
	if (!window.createWindow("Artificial Life Simulation")) {
		std::cerr << "Could not create window or renderer!";
		return 1;
	}

    Map map(3000, 3000);
    auto anim1 = std::unique_ptr<MapObject>(new Animal(100, 200));
    map.addObject(anim1);
    auto anim2 = std::unique_ptr<MapObject>(new Animal(400, 600));
    map.addObject(anim2);
    SDL_FRect rect = {};
    rect.x = 100;
    rect.y = 100;
    rect.h = 200;
    rect.w = 200;
    SDL_Color color = { 127, 80, 180, 255 };
    auto elem1 = std::unique_ptr<Drawable>(new FilledRect(rect, color));
    window.addMenuElement(elem1);

	Simulation simulation(window, map);
	simulation.launch();

	SDL_Quit();
}