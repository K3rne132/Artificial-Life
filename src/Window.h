#pragma once
#include <vector>
#include <memory>
#include "SDL.h"
#include "Drawable.h"
#include "Camera.h"
#undef main
using Size = baseSize<int>;
using FSize = baseSize<float>;

class Window {
private:
	SDL_Window* _Window;
	SDL_Renderer* _Renderer;
	Size _Size;
	std::vector<std::unique_ptr<Drawable>> _MenuElements;
	std::vector<std::unique_ptr<Drawable>> _Targets;
	FSize _Scale;
	Camera _Camera;

	void drawBorder();

public:
	Window(int width, int height) : _Window(nullptr), _Renderer(nullptr),
		_Size(width, height), _Scale(1.f, 1.f),
		_Camera(width, height) {}

	~Window() {
		if (_Renderer)
			SDL_DestroyRenderer(_Renderer);
		if (_Window)
			SDL_DestroyWindow(_Window);
	}

	SDL_FPoint getWindowSize();
	void setWindowSize(int width, int height);
	void setWindowSize(SDL_FPoint size);
	void scaleWindow(float width, float height);
	void zoomIn();
	void zoomOut();
	void moveCamera(float x, float y);
	void stopMoveCamera();
	bool createWindow(const char* title);
	void addMenuElement(std::unique_ptr<Drawable>& drawable);
	void addTarget(std::unique_ptr<Drawable>& drawable);
	void render();

	operator SDL_Renderer* () { return _Renderer; }
	operator SDL_Window* () { return _Window; }
};