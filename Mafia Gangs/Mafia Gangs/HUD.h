#pragma once
#include "Rect.h"
#include "Text.h"

class HUD {
public:
	static SDL_Texture* outside;
	Rect* houtside;
	Rect* health;
	Rect* soutside;
	Rect* stamina;
	Text* ammo;
	Text* enemiesLeft;
	Text* fpsCounter;
	Text* score;
	std::string gunName;
	unsigned int scorevalue;
	unsigned int elvalue;
	unsigned int mammovalue;
	unsigned int rammovalue;
	unsigned int hvalue;
	float svalue;
	HUD(int w, int h, int x, int y, unsigned int hvalue, float svalue, std::string gunName,unsigned int mammovalue, unsigned int rammovalue, unsigned int elvalue, unsigned int scorevalue);
	void updateHealth();
	void updateStamina();
	void updateAmmo();
	void updateEnemiesLeft();
	void updateFPSCounter(int fps);
	void updateScore();
	void draw();
private:
};