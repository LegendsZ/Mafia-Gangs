#include "Bullet.h"

Bullet::Bullet(int w, int h, int x, int y, char direction, SDL_Texture* texture):
	m_bullet(new Rect(w,h,x,y,0,0,0,255)), m_direction(direction)
{
	m_bullet->m_Texture = texture;
}

bool Bullet::move(int velocity)
{
	switch (m_direction) {
	case 'w':
		m_bullet->setDisplacement(0, -velocity);
		break;
	case 'a':
		m_bullet->setDisplacement(-velocity, 0);
		break;
	case 's':
		m_bullet->setDisplacement(0, velocity);
		break;
	case 'd':
		m_bullet->setDisplacement(velocity, 0);
		break;
	}
	return true;
}

bool Bullet::draw(int screenSizeX, int screenSizeY)
{
	int x = m_bullet->getPos()[0];
	int y = m_bullet->getPos()[1];
	if (x >= -m_bullet->m_Width && x < screenSizeX && y >= -m_bullet->m_Height && y < screenSizeY) {
		m_bullet->draw();
	}
	return true;
}

bool Bullet::checkCollision()
{
	return false;
}
