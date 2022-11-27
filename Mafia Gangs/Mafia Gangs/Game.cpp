#include "Game.h"

//bool Menu::enabled;
int Game::screenSizeX, Game::screenSizeY;
unsigned int Game::mouseX, Game::mouseY;
float Game::magnification = 2;
//Rect* Game::bkgdGame;
Rect* Game::bkgdsGame[9];
Dialog* Game::dialog = nullptr;
HUD* Game::hud = nullptr;

Player* Game::player;
Rect* Player::player;
float Player::playerSpeed = 2;
float Player::basePlayerSpeed = Player::playerSpeed;
float Player::runSpeed = 4;
bool Player::run = false;
Uint32 Player::shiftLetGo = NULL;
bool Player::w = false;
bool Player::a = false;
bool Player::s=false;
bool Player::d=false;

bool Game::Initialize(bool enabled, int screenSizeX, int screenSizeY) {
	visibilities::gameVisibility = enabled;
	Game::screenSizeX = screenSizeX;
	Game::screenSizeY = screenSizeY;
	int counter = 0;

	SDL_Surface* surface = IMG_Load("res/bkgdGame.jpg");
	if (!surface) {
		std::cerr << "Failed to create surface!\n";
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create texture!\n";
		return false;
	}
	SDL_FreeSurface(surface);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			Game::bkgdsGame[counter] = (new Rect(screenSizeX * magnification, screenSizeY * magnification, screenSizeX * magnification * (i - 1), screenSizeY * magnification * (j - 1), 255, 255, 255, 1));
			Game::bkgdsGame[counter++]->m_Texture = texture;
		}
	}
	Game::player = new Player();
	player->player = new Rect(25, 25, screenSizeX / 2 - 12.5, screenSizeY / 2 - 12.5, 255, 0, 0, 255);
	hud = new HUD(100, 50, 0, screenSizeY - 50, "res/healthBarOutline.png",100,100);
	return true;
}

bool Game::draw() {
	for (int i = 0; i < 9; i++) {
		Game::bkgdsGame[i]->draw();
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
	if (player->w) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, Player::playerSpeed);
		}
	}
	if (player->a) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(Player::playerSpeed,0);
		}
	}
	if (player->s) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, -Player::playerSpeed);
		}
	}
	if (player->d) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(-Player::playerSpeed,0);
		}
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
	}else if (bkgdsGame[4]->m_Pos[0] <= -screenSizeX) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(screenSizeX * magnification, 0);
		}
	} else if (bkgdsGame[4]->m_Pos[1] >= screenSizeY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0,-screenSizeY * magnification);
		}
	}
	else if (bkgdsGame[4]->m_Pos[1] <= -screenSizeY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0, screenSizeY * magnification);
		}
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
		case SDLK_LSHIFT:
			if (!player->run){
				player->run = true;
				player->playerSpeed =player->runSpeed;
			}
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
		case SDLK_LSHIFT:
			player->shiftLetGo = SDL_GetTicks();
			player->run = false;
			player->playerSpeed =player->basePlayerSpeed;
			break;
		}
	}
	return true;
}