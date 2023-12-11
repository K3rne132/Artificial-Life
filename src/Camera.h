#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"

class Camera {
private:
	float _Zoom;
	float _Width, _Height;
	const float _MapWidth, _MapHeight;
	SDL_FPoint _Offset;
	SDL_FPoint _OldOffset;

	void adjustOffset() {
		if (_Offset.x < -10.f)
			_Offset.x = -10.f;
		if (_Offset.y < -10.f)
			_Offset.y = -10.f;
		if (_Offset.x + _Width > _MapWidth + 10.f)
			_Offset.x = _MapWidth - _Width + 10.f;
		if (_Offset.y + _Height > _MapHeight + 10.f)
			_Offset.y = _MapHeight - _Height + 10.f;
	}

public:
	Camera(float width, float height) :  _Zoom(1.f), _Width(width),
		_Height(height), _MapWidth(width), _MapHeight(height),
		_OldOffset({ 0,0 }), _Offset({ 0,0 }) {}

	float getZoom() { return _Zoom; }
	void setZoom(float zoom) {
		if (zoom < 1.f)
			_Zoom = 1.f;
		else if (zoom > 2.5f)
			_Zoom = 2.5f;
		else
			_Zoom = zoom;
		float old_width = _Width;
		float old_height = _Height;
		_Width = _MapWidth / _Zoom;
		_Height = _MapHeight / _Zoom;
		_Offset.x += (old_width - _Width) / 2;
		_Offset.y += (old_height - _Height) / 2;
		_OldOffset = _Offset;
		adjustOffset();
	}
	SDL_FPoint getOffset() {
		return _Offset;
	}
	SDL_FPoint getCenter() {
		SDL_FPoint center = {};
		center.x = _Offset.x + _Width / 2;
		center.y = _Offset.y + _Height / 2;
		return center;
	}
	void setOffset(SDL_FPoint offset) {
		_Offset.x = _OldOffset.x + offset.x / _Zoom;
		_Offset.y = _OldOffset.y + offset.y / _Zoom;
		adjustOffset();
	}
	void storeOffset() {
		_OldOffset = _Offset;
	}

};