#include "Bullet.h"
SDL_Texture* Bullet::impactTexture;
Bullet::Bullet(int w, int h, int x, int y, int logicalX, int logicalY, char direction, SDL_Texture* texture):
	m_bullet(new Rect(w,h,x,y,0,0,0,255)), m_direction(direction), x(logicalX), y(logicalY)
{
	m_bullet->m_Texture = texture;
}

bool Bullet::move(int velocity)
{
	switch (m_direction) {
	case 'w':
		m_bullet->setDisplacement(0, -velocity);
		y -= velocity;
		break;
	case 'a':
		m_bullet->setDisplacement(-velocity, 0);
		x -= velocity;
		break;
	case 's':
		m_bullet->setDisplacement(0, velocity);
		y += velocity;
		break;
	case 'd':
		m_bullet->setDisplacement(velocity, 0);
		x += velocity;
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

bool Bullet::checkCollision(int velocity)
{
	int lx = x, ly = y;
	if (m_direction == 'w') {
		ly -= velocity;
	}
	else if (m_direction == 's') {
		ly += velocity;
	}
	else if (m_direction == 'a') {
		lx -= velocity;
	}
	else {
		lx += velocity;
	}
	return CollisionMap::checkCollision(m_bullet->m_Width, m_bullet->m_Height, lx, ly);
}
