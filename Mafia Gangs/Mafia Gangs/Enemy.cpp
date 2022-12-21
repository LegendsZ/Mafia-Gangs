#include "Enemy.h"
SDL_Texture* Enemy::wT=nullptr;
SDL_Texture* Enemy::aT=nullptr;
SDL_Texture* Enemy::sT=nullptr;
SDL_Texture* Enemy::dT=nullptr;

Enemy::Enemy(int w, int h, int x, int y, float runSpeed, float baseEnemySpeed) :
	x(x), y(y), enemySpeed(baseEnemySpeed), baseEnemySpeed(baseEnemySpeed),runSpeed(runSpeed), run(false)
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

void Enemy::gameLogic(int pX, int pY)
{

}
