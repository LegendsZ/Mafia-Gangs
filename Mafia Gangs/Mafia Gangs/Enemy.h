#pragma once
#include <vector>
#include "Rect.h"
#include "Bullet.h"
#include "Gun.h"

struct Enemy {
public:
	Rect* enemy;
	int x;
	int y;
	float enemySpeed;
	float baseEnemySpeed;
	float runSpeed;
	float reach;
	bool run;
	static SDL_Texture* wT;
	static SDL_Texture* aT;
	static SDL_Texture* sT;
	static SDL_Texture* dT;

	Enemy(int w, int h, int x, int y, float runSpeed, float baseEnemySpeed, float reach);
	bool setDisplacement(int x, int y);
	int gameLogic(int pX, int pY, std::vector<Bullet*> bullets, Gun* gun);
};