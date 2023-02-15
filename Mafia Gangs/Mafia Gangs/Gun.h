#pragma once
#include "Bullet.h"
#include <vector>
#include "Audio.h"

class Gun {
public:
	std::string m_name;
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
	std::vector<Rect*> m_effects;
	std::vector<Uint32> m_effectsTimes;
	char m_direction;

	static Mix_Chunk* shootsound;
	static Mix_Chunk* reloadsound;

	Gun(std::string name, int reserveAmmo, int magSize, int bulletWidth, int bulletHeight, int bulletVelocity, Uint32 coolDown);

	bool drawBullets(int screenSizeX, int screenSizeY);
	bool drawEffects(int screenSizeX, int screenSizeY);
	bool fire(int x, int y, int logicalX, int logicalY);
	void setEffectsDisplacement(int dx, int dy);
	bool moveBullets();
	void handleEffects();
	bool setBulletDisplacement(int x, int y);
	bool checkCollision();
	bool deleteBullets();
	bool reload();
private:
};