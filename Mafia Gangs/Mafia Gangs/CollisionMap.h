#pragma once

struct Divided {
public:
	unsigned char b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1, b8 : 1;
};

class CollisionMap {
public:
	static Divided* map;
	static unsigned int screenSizeX;
	static unsigned int screenSizeY;
	static bool makeMap(int w, int h);
	static bool checkCollision(int w, int h, int x, int y);
	static bool helper(Divided div, char offset);
private:
};