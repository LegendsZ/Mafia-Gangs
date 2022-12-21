#pragma once
#include "Rect.h"

struct Enemy {
public:
	Rect* enemy;
	int x;
	int y;
	float enemySpeed;
	float baseEnemySpeed;
	float runSpeed;
	bool run;
	static SDL_Texture* wT;
	static SDL_Texture* aT;
	static SDL_Texture* sT;
	static SDL_Texture* dT;

	Enemy(int w, int h, int x, int y, float runSpeed, float baseEnemySpeed);
	bool setDisplacement(int x, int y);
	void gameLogic(int pX, int pY);
};