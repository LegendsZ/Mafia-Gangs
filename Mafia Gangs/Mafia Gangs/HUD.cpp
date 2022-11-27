#include "HUD.h"

HUD::HUD(int w, int h, int x, int y, std::string pathOutside, unsigned int hvalue, unsigned int svalue):
	hvalue(hvalue),svalue(svalue)
{
	houtside = new Rect(w, h, x, y, pathOutside);
	health = new Rect(w, h, x, y, 0,255,0,1);
	if (hvalue != 100) {
		updateHealth();
	}
	soutside = new Rect(w, h, x + w, y, 0, 0, 0, 1);
	soutside->m_Texture = houtside->m_Texture;
	stamina = new Rect(w, h, x+w, y, 255, 255, 0, 1);
	if (svalue != 100) {
		updateStamina();
	}
}

void HUD::updateHealth()
{
	float percent = (float)hvalue / 100;
	health->m_Width = houtside->m_Width * percent;
}
void HUD::updateStamina()
{
	float percent = (float)svalue / 100;
	stamina->m_Width = soutside->m_Width * percent;
}


void HUD::draw()
{
	houtside->draw();
	health->draw();
	soutside->draw();
	stamina->draw();
}
