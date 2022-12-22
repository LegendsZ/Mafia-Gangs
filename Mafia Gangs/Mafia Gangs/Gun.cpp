#include "Gun.h"

SDL_Texture* Gun::wT = nullptr;
SDL_Texture* Gun::aT = nullptr;
SDL_Texture* Gun::sT = nullptr;
SDL_Texture* Gun::dT = nullptr;

Gun::Gun(int reserveAmmo, int magSize, int bulletWidth, int bulletHeight, int bulletVelocity, Uint32 coolDown,std::string texturePath):
	m_lastShot(NULL), m_coolDown(coolDown),m_reserveAmmo(reserveAmmo), m_magSize(magSize), m_magAmmo(magSize), m_bulletWidth(bulletWidth), m_bulletHeight(bulletHeight), m_direction('w'), m_bulletVelocity(bulletVelocity)
{
}

bool Gun::drawBullets(int screenSizeX, int screenSizeY)
{
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i]->draw(screenSizeX, screenSizeY);
	}
	return true;
}

bool Gun::fire(int x, int y) {
	if (SDL_GetTicks() - m_lastShot < m_coolDown) { //cool down
		return false;
	}
	if (m_magAmmo == 0) {
		return false;
	}
	Bullet* bullet = new Bullet(m_bulletWidth, m_bulletHeight, x,y,m_direction, nullptr);
	switch (m_direction) {
	case 'w':
		bullet->m_bullet->m_Texture = Gun::wT;
		break;
	case 'a':
		bullet->m_bullet->m_Texture = Gun::aT;
		break;
	case 's':
		bullet->m_bullet->m_Texture = Gun::sT;
		break;
	case 'd':
		bullet->m_bullet->m_Texture = Gun::dT;
		break;
	}
	m_bullets.push_back(bullet);
	m_lastShot = SDL_GetTicks();
	m_magAmmo -= 1;
	return true;
}

bool Gun::moveBullets()
{
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i]->move(m_bulletVelocity);
	}
	return true;
}

bool Gun::reload() {
	int reFill = m_magSize - m_magAmmo;
	if (reFill <= m_reserveAmmo) {
		m_reserveAmmo -= reFill;
		m_magAmmo = m_magSize;
	}
	else {
		m_magAmmo += m_reserveAmmo;
		m_reserveAmmo = 0;
	}
 	return true;
	
}
bool Gun::setBulletDisplacement(int x, int y)
{
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i]->m_bullet->setDisplacement(x,y);
	}
	return true;
}
bool Gun::checkCollision() {
	for (int i = 0; i < m_bullets.size(); i++) {
		if (m_bullets[i]->checkCollision()) {
			return true;
		}
	}
	return false;
}