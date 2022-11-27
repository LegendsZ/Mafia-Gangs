#pragma once
#include "Rect.h"

class HUD {
public:
	Rect* houtside;
	Rect* health;
	Rect* soutside;
	Rect* stamina;
	unsigned int hvalue;
	unsigned int svalue;
	HUD(int w, int h, int x, int y, std::string pathOutside, unsigned int hvalue, unsigned int svalue);
	void updateHealth();
	void updateStamina();
	void draw();
private:
};