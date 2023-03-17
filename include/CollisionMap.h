#pragma once
#include "Rect.h"

struct Divided {
public:
	unsigned char b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1, b8 : 1;
};

class CollisionMap {
public:
	static SDL_Surface* collisionImage;
	static Divided* map;
	static bool** basicMap;
	static unsigned int screenSizeX;
	static unsigned int screenSizeY;
	static bool makeMap(int w, int h, int magX, int magY);
	static bool checkCollision(int w, int h, int x, int y);
	static bool helper(Divided div, char offset);
private:
};