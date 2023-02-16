#include "Enemy.h"
SDL_Texture* Enemy::wT=nullptr;
SDL_Texture* Enemy::aT=nullptr;
SDL_Texture* Enemy::sT=nullptr;
SDL_Texture* Enemy::dT=nullptr;

Enemy::Enemy(int w, int h, int x, int y, float runSpeed, float baseEnemySpeed,float activitySpeed, float reach) :
	x(x), y(y), enemySpeed(baseEnemySpeed), baseEnemySpeed(baseEnemySpeed),runSpeed(runSpeed), run(false), reach(reach), activitySpeed(activitySpeed)
{
	enemy = new FRect(w, h, x, y, 0, 0, 255, 255);
	enemy->m_Texture = wT;
}

bool Enemy::setDisplacement(int x, int y)
{
	//this->x+= x;
	//this->y += y;
	enemy->setDisplacement(x, y);
	return true;
}

int Enemy::gameLogic(int pX, int pY, std::vector<Bullet*> bullets, Gun* gun)
{
	if (CollisionMap::checkCollision(enemy->m_Width, enemy->m_Height, x, y)) {
		enemySpeed = activitySpeed;
	}
	else {
		enemySpeed = baseEnemySpeed;
	}
	for (int i = 0; i < bullets.size(); i++) {
		int xl = bullets[i]->x; ;// bullets[i]->m_bullet->getPos()[0];
		int yl = bullets[i]->y; //bullets[i]->m_bullet->getPos()[1];
		if (abs(x - xl) <= gun->m_bulletVelocity && abs(y - yl) <= gun->m_bulletVelocity) {
			return i;
		}
	}

	if (abs(x-pX) <=reach&& abs(y-pY)<=reach) {
		return -1;
	}

	if (pX - (int)x < reach) {
		x-=enemySpeed;
		enemy->setDisplacement(-enemySpeed, 0); //commenting these out seems to revert.
		/*if ((int)x == x) {
			enemy->m_Pos[0] = x;
		}*/
		enemy->m_Texture = Enemy::aT;
	}
	else if (pX - (int)x > reach) {
		x+=enemySpeed;
		enemy->setDisplacement(enemySpeed, 0);
		/*if ((int)x == x) {
			enemy->m_Pos[0] = x;
		}*/
		enemy->m_Texture = Enemy::dT;
	}

	if (pY - (int)y < reach) {
		y-=enemySpeed;
		enemy->setDisplacement(0, -enemySpeed);
		/*if ((int)y == y) {
			enemy->m_Pos[1] = y;
		}*/
		enemy->m_Texture = Enemy::wT;
	}
	else if (pY - (int)y > reach) {
		y+=enemySpeed;
		enemy->setDisplacement(0, enemySpeed);
		/*if ((int)y == y) {
			enemy->m_Pos[1] = y;
		}*/
		enemy->m_Texture = Enemy::sT;
	}
	return -2;
}
