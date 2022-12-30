#include "HUD.h"

#include <string>

SDL_Texture* HUD::outside = nullptr;

HUD::HUD(int w, int h, int x, int y, unsigned int hvalue, unsigned int svalue, std::string gunName, unsigned int mammovalue, unsigned int rammovalue, unsigned int elvalue, unsigned int scorevalue) :
	hvalue(hvalue), svalue(svalue), gunName(gunName), mammovalue(mammovalue), rammovalue(rammovalue), elvalue(elvalue), scorevalue(scorevalue)
{
	houtside = new Rect(w, h, x, y, 0,0,0,255);
	houtside->m_Texture = HUD::outside;
	health = new Rect(w, h, x, y, 0,255,0,1);
	if (hvalue != 100) {
		updateHealth();
	}
	soutside = new Rect(w, h, x + w, y, 0, 0, 0, 1);
	soutside->m_Texture = HUD::outside;
	stamina = new Rect(w, h, x+w, y, 255, 255, 0, 1);
	if (svalue != 100) {
		updateStamina();
	}
	ammo = new Text(Window::renderer, "res/comic.ttf", 35, gunName + " " + std::to_string(mammovalue) + "/" + std::to_string(rammovalue), {255,0,0,255});
	ammo->setPos(x + 2 * w + 10, y);
	enemiesLeft = new Text(Window::renderer, "res/comic.ttf", 35, "Enemies Left: " + std::to_string(elvalue), { 0,255,0,255 });
	enemiesLeft->setPos(ammo->getPos()[0] + ammo->m_TextRect.w+10, y);

	fpsCounter = new Text(Window::renderer, "res/comic.ttf", 35, "FPS: 0", { 0,0,255,255 });
	fpsCounter->setPos(enemiesLeft->getPos()[0] + enemiesLeft->m_TextRect.w + 10, y);

	score = new Text(Window::renderer, "res/comic.ttf", 35, "Cash: " + std::to_string(scorevalue) + "$", {255,0,127,255});
	score->setPos(fpsCounter->getPos()[0] + fpsCounter->m_TextRect.w + 10, y);
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

void HUD::updateAmmo()
{
	std::string text = gunName + " " + std::to_string(mammovalue) + "/" + std::to_string(rammovalue);
	ammo->setText(text);
	enemiesLeft->setPos(ammo->getPos()[0] + ammo->m_TextRect.w+10, ammo->getPos()[1]);
}

void HUD::updateEnemiesLeft()
{
	std::string text =  "Enemies Left: " + std::to_string(elvalue);
	enemiesLeft->setText(text);
	fpsCounter->setPos(enemiesLeft->getPos()[0] + enemiesLeft->m_TextRect.w + 10, enemiesLeft->getPos()[1]);
}

void HUD::updateFPSCounter(int fps)
{
	std::string text = "FPS: " + std::to_string(fps);
	fpsCounter->setText(text);
	score->setPos(fpsCounter->getPos()[0] + fpsCounter->m_TextRect.w + 10, fpsCounter->getPos()[1]);
}

void HUD::updateScore()
{
	std::string text = "Cash: " + std::to_string(scorevalue) + "$";
	score->setText(text);
}


void HUD::draw()
{
	houtside->draw();
	health->draw();
	soutside->draw();
	stamina->draw();
	ammo->display();
	enemiesLeft->display();
	fpsCounter->display();
	score->display();
}
