#include "Gun.h"

SDL_Texture* Gun::wT = nullptr;
SDL_Texture* Gun::aT = nullptr;
SDL_Texture* Gun::sT = nullptr;
SDL_Texture* Gun::dT = nullptr;

Mix_Chunk* Gun::shootsound = nullptr;
Mix_Chunk* Gun::reloadsound = nullptr;

Gun::Gun(std::string name, int reserveAmmo, int magSize, int bulletWidth, int bulletHeight, int bulletVelocity, Uint32 coolDown):
	m_name(name),m_lastShot(NULL), m_coolDown(coolDown),m_reserveAmmo(reserveAmmo), m_magSize(magSize), m_magAmmo(magSize), m_bulletWidth(bulletWidth), m_bulletHeight(bulletHeight), m_direction('w'), m_bulletVelocity(bulletVelocity)
{
}

bool Gun::drawBullets(int screenSizeX, int screenSizeY)
{
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i]->draw(screenSizeX, screenSizeY);
	}
	return true;
}
bool Gun::drawEffects(int screenSizeX, int screenSizeY)
{
	for (int i = 0; i < m_effects.size(); i++) {
		int x = m_effects[i]->getPos()[0];
		int y = m_effects[i]->getPos()[1];
		if (x >= -m_effects[i]->m_Width && x < screenSizeX && y >= -m_effects[i]->m_Height && y < screenSizeY) {
			m_effects[i]->m_Texture = Bullet::impactTexture;
			m_effects[i]->draw();
			int x = 0;
		}
	}
	return true;
}

bool Gun::fire(int x, int y, int logicalX, int logicalY) {
	if (SDL_GetTicks() - m_lastShot < m_coolDown) { //cool down
		return false;
	}
	if (m_magAmmo == 0) {
		return false;
	}
	Audio::playEffect(shootsound, 0, 1);
	Bullet* bullet = new Bullet(m_bulletWidth, m_bulletHeight, x,y,logicalX, logicalY,m_direction, nullptr);
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
void Gun::handleEffects() {
	for (int i = 0; i < m_effects.size(); i++) {
		if (i <= m_effects.size()-1 && SDL_GetTicks() - m_effectsTimes[i] >= 150) {
			Rect::delTexture = false;
			delete m_effects[i];
			Rect::delTexture = true;
			m_effects.erase(m_effects.begin() + i);
			m_effectsTimes.erase(m_effectsTimes.begin() + i);
		}
	}
}
void Gun::setEffectsDisplacement(int dx, int dy) {
	for (int i = 0; i < m_effects.size(); i++) {
		m_effects[i]->setDisplacement(dx, dy);
	}
}

bool Gun::reload() {
	if (m_magAmmo == m_magSize) {
		return false;
	}
	Audio::playEffect(reloadsound, 0, 1);
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
bool Gun::deleteBullets()
{
	for (int i = 0; i < m_bullets.size(); i++) {
		delete m_bullets[i];
	}
	m_bullets.clear();
	return true;
}
bool Gun::checkCollision() {
	bool someDeleted = false;
	for (int i = 0; i < m_bullets.size(); i++) {
		if (i <= m_bullets.size()-1 && m_bullets[i]->checkCollision(m_bulletVelocity)) {
			someDeleted = true;
			int lx = 0, ly = 0;
			if (m_direction == 'w') {
				ly -= m_bulletVelocity;
			}
			else if (m_direction == 's') {
				ly += m_bulletVelocity;
			}
			else if (m_direction == 'a') {
				lx -= m_bulletVelocity;
			}
			else {
				lx += m_bulletVelocity;
			}
			m_effects.push_back(new Rect(m_bullets[i]->m_bullet->m_Width, m_bullets[i]->m_bullet->m_Height, m_bullets[i]->m_bullet->m_Pos[0]+lx, m_bullets[i]->m_bullet->m_Pos[1]+ly, 0,0,0, 255));
			m_effects[m_effects.size() - 1]->m_Texture = Bullet::impactTexture;
			m_effectsTimes.push_back(SDL_GetTicks());
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
	return someDeleted;
}