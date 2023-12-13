#pragma once
#include <vector>
#include <memory>
#include "SDL.h"
#include "Drawable.h"
#include "Camera.h"
#include "PointBase.hpp"
#include "Map.h"

class Window {
private:
	/* A handle to window */
	SDL_Window* _Window;
	/* A handle to renderer surface */
	SDL_Renderer* _Renderer;
	/* A base size of window in pixels / pixels
	   It is almost constant value and do not represent actual
	   window size */
	Point _Size;
	/* A list of menu elements(overlay targets) */
	std::vector<std::unique_ptr<Drawable>> _MenuElements;
	/* A scale of current window meaning:
	   <actual window size> =  _Scale * _Size */
	FPoint _Scale;
	/* An object representing camera (viewport) */
	Camera _Camera;
	std::unique_ptr<Drawable> _Border;

	void drawBorder();

public:
	Window(int width, int height) : _Window(nullptr), _Renderer(nullptr),
		_Size(width, height), _Scale(1.f, 1.f), _Camera(width, height, 0.f, 0.f) {}

	~Window() {
		if (_Renderer)
			SDL_DestroyRenderer(_Renderer);
		if (_Window)
			SDL_DestroyWindow(_Window);
	}

	Point getWindowSize();
	void setWindowSize(int width, int height);
	void setWindowSize(Point size);
	void scaleWindow(float width, float height);
	void scaleWindow(FPoint scale);
	void zoomIn();
	void zoomOut();
	void moveCamera(float x, float y);
	void moveCamera(FPoint offset);
	void stopMoveCamera();
	bool createWindow(const char* title);
	void addMenuElement(std::unique_ptr<Drawable>& drawable);
	void setBorder(std::unique_ptr<Drawable>& border);
	void resetCamera(Point mapsize);
	void render(Map& map);

	operator SDL_Renderer* () { return _Renderer; }
	operator SDL_Window* () { return _Window; }
};