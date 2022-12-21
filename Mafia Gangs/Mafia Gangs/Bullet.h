#pragma once
#include "Rect.h"

class Bullet {
public:
	Rect* m_bullet;
	char m_direction;

	Bullet(int w, int h, int x, int y, char direction, SDL_Texture* texture);
	bool move(int velocity);
	bool draw(int screenSizeX, int screenSizeY);
	bool checkCollision();
private:
};