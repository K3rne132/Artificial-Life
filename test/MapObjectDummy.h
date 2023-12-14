#include <MapObject.h>

class MapObjectDummy : public MapObject {
public:
	MapObjectDummy(int x, int y) : MapObject(x, y) {}
	void draw(SDL_Renderer* renderer, FPoint offset) override  {}
};