#pragma once
#include "Rect.h"
#include "CollisionMap.h"

class Bullet {
public:
	Rect* m_bullet;
	char m_direction;
	int x, y;
	static SDL_Texture* impactTexture;

	Bullet(int w, int h, int x, int y, int logicalX, int logicalY,char direction, SDL_Texture* texture);
	bool move(int velocity);
	bool draw(int screenSizeX, int screenSizeY);
	bool checkCollision(int velocity);
private:
};