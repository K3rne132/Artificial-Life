#include "Window.h"

void Window::drawBorder() {
	SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
	int offsetx = _Camera.getOffset().x;
	int offsety = _Camera.getOffset().y;
	SDL_Rect border = SDL_Rect{ -offsetx, -offsety, _Width, _Height };
	SDL_RenderDrawRect(_Renderer, &border);
}

SDL_FPoint Window::getWindowSize() {
	SDL_FPoint size = {};
	size.x = _Width;
	size.y = _Height;
	return size;
}

void Window::setWindowSize(int width, int height) {
	_Width = width;
	_Height = height;
	if (_Window)
		SDL_SetWindowSize(_Window, width, height);
}

void Window::setWindowSize(SDL_FPoint size) {
	setWindowSize(size.x, size.y);
}

void Window::scaleWindow(float width, float height) {
	_ScaleX = width / _Width;
	_ScaleY = height / _Height;
	SDL_RenderSetScale(_Renderer, _ScaleX, _ScaleY);
}

void Window::zoomIn() {
	_Camera.setZoom(_Camera.getZoom() * 1.15f);
}

void Window::zoomOut() {
	_Camera.setZoom(_Camera.getZoom() * 0.9f);
}

void Window::moveCamera(float x, float y) {
	_Camera.setOffset(SDL_FPoint{ x, y });
}

void Window::stopMoveCamera() {
	_Camera.storeOffset();
}

bool Window::createWindow(const char* title) {
	_Window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_Width,
		_Height,
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

void Window::addTarget(std::unique_ptr<Drawable>& drawable) {
	_Targets.push_back(std::move(drawable));
}

void Window::render() {
	SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(_Renderer);
	SDL_RenderSetScale(_Renderer,
		_ScaleX * _Camera.getZoom(),
		_ScaleY * _Camera.getZoom());
	drawBorder();
	for (const auto& target : _Targets)
		target->draw(_Renderer, _Camera.getOffset());
	SDL_RenderSetScale(_Renderer, _ScaleX, _ScaleY);
	for (const auto& element : _MenuElements)
		element->draw(_Renderer);
	SDL_RenderPresent(_Renderer);
}