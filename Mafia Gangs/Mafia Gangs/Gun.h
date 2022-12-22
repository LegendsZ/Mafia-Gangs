#pragma once
#include "Bullet.h"
#include <vector>

class Gun {
public:
	int m_reserveAmmo;
	int m_magSize;
	int m_magAmmo;
	int m_bulletWidth;
	int m_bulletHeight;
	int m_bulletVelocity;
	Uint32 m_coolDown;
	Uint32 m_lastShot;

	static SDL_Texture* wT;
	static SDL_Texture* aT;
	static SDL_Texture* sT;
	static SDL_Texture* dT;

	std::vector<Bullet*> m_bullets;
	char m_direction;

	Gun(int reserveAmmo, int magSize, int bulletWidth, int bulletHeight, int bulletVelocity, Uint32 coolDown, std::string texturePath);

	bool drawBullets(int screenSizeX, int screenSizeY);
	bool fire(int x, int y);
	bool moveBullets();
	bool setBulletDisplacement(int x, int y);
	bool checkCollision();
	bool reload();
private:
};