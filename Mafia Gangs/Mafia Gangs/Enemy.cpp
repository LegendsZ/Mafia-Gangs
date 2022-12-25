#include "Enemy.h"
SDL_Texture* Enemy::wT=nullptr;
SDL_Texture* Enemy::aT=nullptr;
SDL_Texture* Enemy::sT=nullptr;
SDL_Texture* Enemy::dT=nullptr;

Enemy::Enemy(int w, int h, int x, int y, float runSpeed, float baseEnemySpeed, float reach) :
	x(x), y(y), enemySpeed(baseEnemySpeed), baseEnemySpeed(baseEnemySpeed),runSpeed(runSpeed), run(false), reach(reach)
{
	enemy = new Rect(w, h, x, y, 0, 0, 255, 255);
	enemy->m_Texture = wT;
}

bool Enemy::setDisplacement(int x, int y)
{
	this->x+= x;
	this->y += y;
	enemy->setDisplacement(x, y);
	return true;
}

int Enemy::gameLogic(int pX, int pY, std::vector<Bullet*> bullets, Gun* gun)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (abs(x - bullets[i]->m_bullet->getPos()[0]) <= gun->m_bulletVelocity && abs(y - bullets[i]->m_bullet->getPos()[1]) <= gun->m_bulletVelocity) {
			return i;
		}
	}

	if (abs(x-pX) <=reach&& abs(y-pY)<=reach) {
		return -1;
	}

	if (pX - x < 0) {
		x--;
		enemy->setDisplacement(-1, 0);
		enemy->m_Texture = Enemy::aT;
	}
	else if (pX - x > 0) {
		x++;
		enemy->setDisplacement(1, 0);
		enemy->m_Texture = Enemy::dT;
	}

	if (pY - y < 0) {
		y--;
		enemy->setDisplacement(0, -1);
		enemy->m_Texture = Enemy::wT;
	}
	else if (pY - y > 0) {
		y++;
		enemy->setDisplacement(0, 1);
		enemy->m_Texture = Enemy::sT;
	}
	return -2;
}
