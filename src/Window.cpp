#include "Window.h"

void Window::drawBorder() {
	SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
	int offsetx = _Camera.getOffset().X;
	int offsety = _Camera.getOffset().Y;
	SDL_Rect border = SDL_Rect{ -offsetx, -offsety, _Size.X, _Size.Y };
	SDL_RenderDrawRect(_Renderer, &border);
}

Point Window::getWindowSize() {
	return _Size;
}

void Window::setWindowSize(int width, int height) {
	_Size.X = width;
	_Size.Y = height;
	if (_Window)
		SDL_SetWindowSize(_Window, width, height);
}

void Window::setWindowSize(Point size) {
	setWindowSize(size.X, size.Y);
}

void Window::scaleWindow(float width, float height) {
	_Scale.X = width / _Size.X;
	_Scale.Y = height / _Size.Y;
	SDL_RenderSetScale(_Renderer, _Scale.X, _Scale.Y);
}

void Window::scaleWindow(FPoint scale) {
	scaleWindow(scale.X, scale.Y);
}

void Window::zoomIn() {
	_Camera.setZoom(_Camera.getZoom() * 1.15f);
}

void Window::zoomOut() {
	_Camera.setZoom(_Camera.getZoom() * 0.9f);
}

void Window::moveCamera(float x, float y) {
	moveCamera(FPoint(x, y));
}

void Window::moveCamera(FPoint offset) {
	_Camera.setOffset(offset);
}

void Window::stopMoveCamera() {
	_Camera.storeOffset();
}

bool Window::createWindow(const char* title) {
	_Window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_Size.X,
		_Size.Y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	if (_Window == nullptr)
		return false;
	_Renderer = SDL_CreateRenderer(
		_Window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (_Renderer == nullptr) {
		SDL_DestroyWindow(_Window);
		return false;
	}
	return true;
}

void Window::addMenuElement(std::unique_ptr<Drawable>& drawable) {
	_MenuElements.push_back(std::move(drawable));
}

void Window::setBorder(std::unique_ptr<Drawable>& border) {
	_Border = std::move(border);
}

void Window::resetCamera(Point mapsize) {
	_Camera.setMapSize(mapsize);
}

void Window::render(Map& map) {
	SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(_Renderer);
	SDL_RenderSetScale(_Renderer,
		_Scale.X * _Camera.getZoom(),
		_Scale.Y * _Camera.getZoom());
	if (_Border)
		_Border->draw(_Renderer, !_Camera.getOffset());
	for (const auto& object : map)
		object->draw(_Renderer, !_Camera.getOffset());
	SDL_RenderSetScale(_Renderer, _Scale.X, _Scale.Y);
	for (const auto& element : _MenuElements)
		element->draw(_Renderer);
	SDL_RenderPresent(_Renderer);
}