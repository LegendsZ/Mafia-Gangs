#include "Game.h"

//bool Menu::enabled;
int Game::screenSizeX, Game::screenSizeY;
unsigned int Game::mouseX, Game::mouseY;
float Game::magnification = 2;
//Rect* Game::bkgdGame;
Rect* Game::bkgdsGame[9];
Dialog* Game::dialog = nullptr;
HUD* Game::hud = nullptr;
bool Game::loaded = false;
Player* Game::player;

int Player::x;
int Player::y;
Rect* Player::player;
float Player::playerSpeed = 1*Game::magnification;
float Player::basePlayerSpeed = Player::playerSpeed;
float Player::runSpeed = 2*Game::magnification;
bool Player::run = false;
Uint32 Player::shiftLetGo = NULL;
bool Player::w = false;
bool Player::a = false;
bool Player::s=false;
bool Player::d=false;

SDL_Texture* Player::wT = nullptr;
SDL_Texture* Player::aT = nullptr;
SDL_Texture* Player::sT = nullptr;
SDL_Texture* Player::dT = nullptr;

std::vector<Enemy*> Game::enemies;
Gun* gun;

bool Game::Initialize(bool enabled, int screenSizeX, int screenSizeY) {
	visibilities::gameVisibility = enabled;
	Game::screenSizeX = screenSizeX;
	Game::screenSizeY = screenSizeY;
	int counter = 0;

	SDL_Texture* texture = Rect::getTexture("res/bkgdGame.jpg");
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			Game::bkgdsGame[counter] = (new Rect(screenSizeX * magnification, screenSizeY * magnification, screenSizeX * magnification * (i - 1), screenSizeY * magnification * (j - 1), 255, 255, 255, 1));
			Game::bkgdsGame[counter++]->m_Texture = texture;
		}
	}
	Game::player = new Player();
	player->x = screenSizeX * magnification / 2;
	player->y = screenSizeY * magnification / 2;
	player->player = new Rect(10 * magnification, 10 * magnification, screenSizeX / 2, screenSizeY / 2, 255, 0, 0, 255);



	hud = new HUD(100, 50, 0, screenSizeY - 50, "res/healthBarOutline.png",100,100);
	CollisionMap::makeMap(screenSizeX * magnification, screenSizeY * magnification);

	player->player->m_Texture = Player::wT;

	for (int i = 0; i < 1; i++) {
		enemies.push_back(new Enemy(10 * magnification, 10 * magnification, screenSizeX / 2, screenSizeY / 2, Player::runSpeed, Player::basePlayerSpeed));
	}
	gun = new Gun(10, 3, 20,20,1,"res/bullet.jpg");

	Game::loaded = true;
	return true;
}

bool Game::draw() {
	for (int i = 0; i < 9; i++) {
		Game::bkgdsGame[i]->draw();
	}
	gun->drawBullets(screenSizeX, screenSizeY);
	for (int i = 0; i < enemies.size(); i++) {
		if (Game::enemies[i]->x < screenSizeX && Game::enemies[i]->x >= -Game::enemies[i]->enemy->m_Width && Game::enemies[i]->y < screenSizeY && Game::enemies[i]->y >= -Game::enemies[i]->enemy->m_Height) {
			Game::enemies[i]->enemy->draw();
		}
	}
	Game::player->player->draw();
	Game::hud->draw();
	if (Game::dialog) {
		Game::dialog->draw();
	}
	return true;
}
bool Game::gameLogic() {
	if (hud->svalue != 100 && SDL_GetTicks() - player->shiftLetGo > 3000) {
		hud->svalue++;
		hud->updateStamina();
	}
	if (player->run && hud->svalue != 0) {
		player->shiftLetGo = SDL_GetTicks();
		player->playerSpeed = player->runSpeed;
	}
	if (player->w && CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x, player->y - Player::playerSpeed)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, Player::playerSpeed);
		}
		player->y -= Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(0, Player::playerSpeed);
		}
	}
	if (player->a && CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x - Player::playerSpeed, player->y)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(Player::playerSpeed,0);
		}
		player->x -= Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(Player::playerSpeed,0);
		}
	}
	if (player->s && CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x, player->y + Player::playerSpeed)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, -Player::playerSpeed);
		}
		player->y += Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(0, -Player::playerSpeed);
		}
	}
	if (player->d && CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x + Player::playerSpeed, player->y)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(-Player::playerSpeed,0);
		}
		player->x += Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(-Player::playerSpeed,0);
		}
	}
	if (player->w || player->a || player->s || player->d) {
		system("cls");
		std::cout << "(" << player->x << "," << player->y << ")\n";
	}
	if (player->run && hud->svalue > 0 && (player->w || player->a || player->s || player->d)) {
		hud->svalue--;
		hud->updateStamina();
	}
	if (hud->svalue == 0) {
		player->playerSpeed = player->basePlayerSpeed;
	}

	if (bkgdsGame[4]->m_Pos[0] >= screenSizeX) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(-screenSizeX * magnification, 0);
		}
		
		player->x += screenSizeX * magnification;
	}else if (bkgdsGame[4]->m_Pos[0] <= -screenSizeX) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(screenSizeX * magnification, 0);
		}
		player->x -= screenSizeX * magnification;
	} else if (bkgdsGame[4]->m_Pos[1] >= screenSizeY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0,-screenSizeY * magnification);
		}
		player->y += screenSizeY * magnification;
	}
	else if (bkgdsGame[4]->m_Pos[1] <= -screenSizeY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0, screenSizeY * magnification);
		}
		player->y -= screenSizeY * magnification;
	}

	return true;
}
bool Game::pollEvents()
{
	if (!visibilities::gameVisibility) {
		return false;
	}
	gameLogic();
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x <= screenSizeX ? event.motion.x : mouseX;
		mouseY = event.motion.y <= screenSizeY ? event.motion.y : mouseY;
	}
	pollPlayerControls(event);
	return true;
}

bool Game::pollPlayerControls(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			player->w = true;
			player->player->m_Texture = Player::wT;
			break;
		case SDLK_a:
			player->a = true;
			player->player->m_Texture = Player::aT;
			break;
		case SDLK_s:
			player->s = true;
			player->player->m_Texture = Player::sT;
			break;
		case SDLK_d:
			player->d = true;
			player->player->m_Texture = Player::dT;
			break;
		case SDLK_LSHIFT:
			if (!player->run){
				player->run = true;
				player->playerSpeed =player->runSpeed;
			}
			break;
		case SDLK_SPACE:
			SDL_Texture* localTexture = player->player->m_Texture;
			if (localTexture == Player::wT) {
				gun->m_direction = 'w';
			}else if (localTexture == Player::aT) {
				gun->m_direction = 'a';
			}
			else if(localTexture == Player::sT) {
				gun->m_direction = 's';
			}
			else if(localTexture == Player::dT) {
				gun->m_direction = 'd';
			}
			gun->fire(screenSizeX / 2, screenSizeY / 2);
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			player->w = false;
			break;
		case SDLK_a:
			player->a = false;
			break;
		case SDLK_s:
			player->s = false;
			break;
		case SDLK_d:
			player->d = false;
			break;
		case SDLK_LSHIFT:
			player->shiftLetGo = SDL_GetTicks();
			player->run = false;
			player->playerSpeed =player->basePlayerSpeed;
			break;
		case SDLK_ESCAPE:
			visibilities::gameVisibility = false;
			visibilities::menuVisibility = true;
			SDL_SetWindowTitle(((Window*)visibilities::windowPTRVOID)->m_Window, "Mafia Gangs | Menu");
		}
	}
	return true;
}