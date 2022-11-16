#include "Game.h"

//bool Menu::enabled;
unsigned int Game::screenSizeX, Game::screenSizeY;
unsigned int Game::mouseX, Game::mouseY;
Rect* Game::bkgdGame;
Player* Game::player;

Rect* Player::player;
int Player::playerSpeed = 2;
bool Player::w = false;
bool Player::a = false;
bool Player::s=false;
bool Player::d=false;

bool Game::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	visibilities::gameVisibility = enabled;
	Game::screenSizeX = screenSizeX;
	Game::screenSizeY = screenSizeY;
	Game::bkgdGame = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdGame.jpg");
	Game::player = new Player();
	player->player = new Rect(25, 25, screenSizeX / 2, screenSizeY / 2, 255, 0, 0, 255);
	return true;
}

bool Game::draw() {
	if (visibilities::gameVisibility) {
		Game::bkgdGame->draw();
		Game::player->player->draw();
		return true;
	}
	return false;
}
bool Game::gameLogic() {
	if (player->w) {
		player->player->setDisplacement(0, -Player::playerSpeed);
	}
	if (player->a) {
		player->player->setDisplacement(-Player::playerSpeed, 0);
	}
	if (player->s) {
		player->player->setDisplacement(0, Player::playerSpeed);
	}
	if (player->d) {
		player->player->setDisplacement(Player::playerSpeed, 0);
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
			break;
		case SDLK_a:
			player->a = true;
			break;
		case SDLK_s:
			player->s = true;
			break;
		case SDLK_d:
			player->d = true;
			break;
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
		}
	}
	return true;
}