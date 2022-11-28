#include "CollisionMap.h"

Divided* CollisionMap::map = nullptr;
unsigned int CollisionMap::screenSizeX;
unsigned int CollisionMap::screenSizeY;

bool CollisionMap::makeMap(int w, int h)
{
	CollisionMap::screenSizeX = w;
	CollisionMap::screenSizeY = h;
	int size = w * h / 8;
	map = new Divided[size];
	for (int i = 0; i < size; i++) {
		map[i] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	}
	return true;
}

bool CollisionMap::checkCollision(int w, int h, int x, int y) //check memory it's collecting
{
	int size = w * h / 8;
	int indextl = ((CollisionMap::screenSizeX * y + x) / 8) % size;
	char offsettl = (CollisionMap::screenSizeX * y + x) % 8;
	Divided tl = CollisionMap::map[indextl];

	int indextr = ((CollisionMap::screenSizeX * y + x + w) / 8) % size;
	indextr = indextr % w * h / 8;
	char offsettr = (CollisionMap::screenSizeX * y + x + w) % 8;
	Divided tr = CollisionMap::map[indextr];

	int indexbl = ((CollisionMap::screenSizeX * (y + h) + x) / 8) % size;
	char offsetbl = (CollisionMap::screenSizeX * (y + h) + x) % 8;
	Divided bl = CollisionMap::map[indexbl];

	int indexbr = ((CollisionMap::screenSizeX * (y + h) + x + w) / 8) % size;
	char offsetbr = (CollisionMap::screenSizeX * (y + h) + x + w) % 8;
	Divided br = CollisionMap::map[indexbr];

	return helper(tl, offsettl) && helper(tr, offsettr) && helper(bl, offsetbl) && helper(br, offsetbr);
}

bool CollisionMap::helper(Divided div, char offset)
{
	switch (offset) {
	case 1:
		if (div.b1 == 1) {
			return false;
		}
		break;
	case 2:
		if (div.b2 == 1) {
			return false;
		}
		break;
	case 3:
		if (div.b3 == 1) {
			return false;
		}
		break;
	case 4:
		if (div.b4 == 1) {
			return false;
		}
		break;
	case 5:
		if (div.b5 == 1) {
			return false;
		}
		break;
	case 6:
		if (div.b6 == 1) {
			return false;
		}
		break;
	case 7:
		if (div.b7 == 1) {
			return false;
		}
		break;
	case 0:
		if (div.b8 == 1) {
			return false;
		}
		break;
	}
	return true;
}
