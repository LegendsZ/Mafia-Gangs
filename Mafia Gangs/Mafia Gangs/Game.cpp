#include "Game.h"

//bool Menu::enabled;
int Game::screenSizeX, Game::screenSizeY;
int Game::DEFAULTSCREENX = 1920, Game::DEFAULTSCREENY = 1080; //1250x 750y
unsigned int Game::mouseX, Game::mouseY;
int Game::magnification = 1;
int Game::magnificationX = Game::magnification;
int Game::magnificationY = Game::magnification;
//Rect* Game::bkgdGame;
Rect* Game::bkgdsGame[9];
Dialog* Game::dialog = nullptr;
HUD* Game::hud = nullptr;
bool Game::loaded = false;
bool Game::zombies = false;
Player* Game::player;
Gun* Game::gun = nullptr;

int Player::x;
int Player::y;
Rect* Player::player;
float Player::playerSpeed = 1*Game::magnification;
float Player::basePlayerSpeed = Player::playerSpeed;
float Player::runSpeed = 2 * Player::basePlayerSpeed;
bool Player::run = false;
bool Player::firing = false;
Uint32 Player::shiftLetGo = NULL;
bool Player::w = false;
bool Player::a = false;
bool Player::s=false;
bool Player::d=false;

SDL_Texture* Player::wT = nullptr;
SDL_Texture* Player::aT = nullptr;
SDL_Texture* Player::sT = nullptr;
SDL_Texture* Player::dT = nullptr;

SDL_Texture* Game::bkgd = nullptr;
Mix_Music* Game::bkgdMusic = nullptr;

std::vector<Enemy*> Game::enemies;
unsigned int Game::enemiesSpawn = 10;
MissionManager* missionManager = nullptr;

bool Game::Initialize(bool enabled, int screenSizeX, int screenSizeY) {
	visibilities::gameVisibility = enabled;
	Game::screenSizeX = screenSizeX;
	Game::screenSizeY = screenSizeY;

	Game::magnificationX = ((float)Game::magnificationX / Game::DEFAULTSCREENX) * screenSizeX;//(float)(screenSizeX) / (Game::magnificationX * 800);
	Game::magnificationY = ((float)Game::magnificationY / Game::DEFAULTSCREENY) * screenSizeY;//(float)(screenSizeY) / (Game::magnificationY * 500);
	int counter = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			Game::bkgdsGame[counter] = (new Rect(screenSizeX * Game::magnificationX, screenSizeY * Game::magnificationY, screenSizeX * Game::magnificationX * (i - 1), screenSizeY * Game::magnificationY * (j - 1), 255, 255, 255, 1));
			Game::bkgdsGame[counter++]->m_Texture = Game::bkgd;
		}
	}
	Game::player = new Player();
	player->x = screenSizeX * Game::magnificationX / 2;
	player->y = screenSizeY * Game::magnificationY / 2 + 100;
	player->player = new Rect(20 * Game::magnificationX, 20 * Game::magnificationY, screenSizeX / 2, screenSizeY / 2 + 100, 255, 0, 0, 255);

	
	CollisionMap::makeMap(screenSizeX * Game::magnificationX, screenSizeY * Game::magnificationY, Game::magnificationX, Game::magnificationY);
	player->player->m_Texture = Player::wT;
	
	if (zombies) {
		gun = new Gun("M1911", 32, 8, 20 * Game::magnificationX, 20 * Game::magnificationY, 30, 300);
		hud = new HUD(100, 50, 0, screenSizeY - 50, 100, 100, gun->m_name, gun->m_magAmmo, gun->m_reserveAmmo, Game::enemiesSpawn, 0);
		spawnEnemies(500, Game::enemiesSpawn);
		//spawnEnemies(500, 1);
		Mix_PlayMusic(Game::bkgdMusic, -1); //make audio manager
		Audio::playMusic(Game::bkgdMusic);
	}
	else {
		hud = new HUD(100, 50, 0, screenSizeY - 50, 100, 100,0);
		missionManager = new MissionManager();
		missionManager->loadMissionData();
	}
	Game::loaded = true;
	return true;
}

bool Game::saveClose()
{
	Rect::delTexture = false;
	for (int i = 0; i < 9; i++) {
		delete bkgdsGame[i];
	}
	Rect::delTexture = true;
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
	enemies.clear();
	delete hud;
	delete dialog;
	delete gun;

	Game::loaded = false;
	return true;
}

bool Game::spawnEnemies(int range,int count)
{
	for (int i = 0; i < count; i++) {
		enemies.push_back(new Enemy(20 * Game::magnificationX, 20 * Game::magnificationY, screenSizeX / 2 + (i * (rand() % range)), screenSizeY / 2 + (i * (rand() % range)), Player::runSpeed*0.75, Player::basePlayerSpeed*0.6,Player::basePlayerSpeed/4, 3));
	}
	return true;
}

bool Game::Reset()
{
	gun->deleteBullets();
	gun->m_magAmmo = gun->m_magSize;
	gun->m_reserveAmmo = 32;
	hud->updateAmmo();
	hud->elvalue = Game::enemiesSpawn;
	//int offsetx = player->x - (screenSizeX * Game::magnificationX / 2);
	//int offsety = player->y - (screenSizeY * Game::magnificationY / 2);
	int range = 500;
	int playerOffsetX = player->x - (screenSizeX * Game::magnificationX / 2);
	int playerOffsetY = player->y - (screenSizeY * Game::magnificationY / 2 + 100);
	for (int i = 0; i < enemies.size(); i++) {
		//delete enemies[i];
		enemies[i] = new Enemy(20 * Game::magnificationX, 20 * Game::magnificationY, screenSizeX / 2 + (i * (rand() % range)), screenSizeY / 2 + (i * (rand() % range)), Player::runSpeed * 0.75, Player::basePlayerSpeed * 0.6, Player::basePlayerSpeed / 4, 3);
		enemies[i]->x += playerOffsetX;
		enemies[i]->y += playerOffsetY;
	}
	
	hud->hvalue = 100;
	hud->svalue = 100;
	hud->updateHealth();
	hud->updateStamina();
	return true;
}

bool Game::draw() {
	for (int i = 0; i < 9; i++) {
		Game::bkgdsGame[i]->draw();
	}
	if (gun) {
		gun->drawBullets(screenSizeX, screenSizeY);
		gun->drawEffects(screenSizeX, screenSizeY);
	}
	for (int i = 0; i < enemies.size(); i++) {
		if (Game::enemies[i]->enemy->m_Pos[0] < screenSizeX && Game::enemies[i]->enemy->m_Pos[0] >= -Game::enemies[i]->enemy->m_Width && Game::enemies[i]->enemy->m_Pos[1] < screenSizeY && Game::enemies[i]->enemy->m_Pos[1] >= -Game::enemies[i]->enemy->m_Height) {
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
	for (int i = 0; i < enemies.size(); i++) {
		//int ret = enemies[i]->gameLogic(player->player->getPos()[0], player->player->getPos()[1], gun->m_bullets, gun);
		int ret = enemies[i]->gameLogic(player->x, player->y, gun->m_bullets, gun);
		if (ret == -1) {
			hud->hvalue--;
			hud->updateHealth();
			if (hud->hvalue <= 0) {
				Reset();
			}
		}
		else if (ret >= 0) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			hud->elvalue--;
			hud->updateEnemiesLeft();
			//delete gun->m_bullets[i];
			gun->m_bullets.erase(gun->m_bullets.begin() + ret);
			hud->scorevalue += 10;
			hud->updateScore();
		}
	}
	if (gun) {
		gun->checkCollision();
		gun->handleEffects();
	}
	if (player->firing) {
		SDL_Texture* localTexture = player->player->m_Texture;
		if (localTexture == Player::wT) {
			gun->m_direction = 'w';
		}
		else if (localTexture == Player::aT) {
			gun->m_direction = 'a';
		}
		else if (localTexture == Player::sT) {
			gun->m_direction = 's';
		}
		else if (localTexture == Player::dT) {
			gun->m_direction = 'd';
		}
		if (gun->fire(player->player->getPos()[0], player->player->getPos()[1], player->x, player->y)) {
			hud->mammovalue--;
			hud->updateAmmo();
		}
	}
	if (gun) {
		gun->moveBullets();
	}
	if (hud->svalue != 100 && SDL_GetTicks() - player->shiftLetGo >= 2000) {
		hud->svalue+=0.5;
		hud->updateStamina();
	}
	if (player->run && hud->svalue != 0) {
		player->shiftLetGo = SDL_GetTicks();
		player->playerSpeed = player->runSpeed;
	}
	if (player->w && !CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x, player->y - Player::playerSpeed)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, Player::playerSpeed);
		}
		player->y -= Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(0, Player::playerSpeed);
		}
		if (gun) {
			gun->setBulletDisplacement(0, Player::playerSpeed);
			gun->setEffectsDisplacement(0, Player::playerSpeed);
		}
	}
	if (player->a && !CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x - Player::playerSpeed, player->y)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(Player::playerSpeed,0);
		}
		player->x -= Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(Player::playerSpeed,0);
		}
		if (gun) {
			gun->setBulletDisplacement(Player::playerSpeed,0);
			gun->setEffectsDisplacement(Player::playerSpeed,0);
		}
	}
	if (player->s && !CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x, player->y + Player::playerSpeed)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(0, -Player::playerSpeed);
		}
		player->y += Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(0, -Player::playerSpeed);
		}
		if (gun) {
			gun->setBulletDisplacement(0, -Player::playerSpeed);
			gun->setEffectsDisplacement(0, -Player::playerSpeed);
		}
	}
	if (player->d && !CollisionMap::checkCollision(player->player->m_Width, player->player->m_Height, player->x + Player::playerSpeed, player->y)) {
		for (int i = 0; i < 9; i++) {
			bkgdsGame[i]->setDisplacement(-Player::playerSpeed,0);
		}
		player->x += Player::playerSpeed;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setDisplacement(-Player::playerSpeed,0);
		}
		if (gun) {
			gun->setBulletDisplacement(-Player::playerSpeed,0);
			gun->setEffectsDisplacement(-Player::playerSpeed,0);
		}
	}
	/*if (player->w || player->a || player->s || player->d) {
		system("cls");
		std::cout << "(" << player->x << "," << player->y << ")\n";
	}*/
	if (player->run && hud->svalue > 0 && (player->w || player->a || player->s || player->d)) {
		hud->svalue-=0.5;
		hud->updateStamina();
	}
	if (hud->svalue == 0) {
		player->playerSpeed = player->basePlayerSpeed;
	}

	if (bkgdsGame[4]->m_Pos[0] >= screenSizeX * Game::magnificationX) { //added the * gamemag to each one
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(-screenSizeX * Game::magnificationX, 0);
		}
		//player->x += screenSizeX * Game::magnificationX;
	}else if (bkgdsGame[4]->m_Pos[0] <= -screenSizeX * Game::magnificationX) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(screenSizeX * Game::magnificationX, 0);
		}
	} else if (bkgdsGame[4]->m_Pos[1] >= screenSizeY * Game::magnificationY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0,-screenSizeY * Game::magnificationY);
		}
	}
	else if (bkgdsGame[4]->m_Pos[1] <= -screenSizeY * Game::magnificationY) {
		for (int i = 0; i < 9; i++) {
			Game::bkgdsGame[i]->setDisplacement(0, screenSizeY * Game::magnificationY);
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
			if (gun) {
				player->firing = true;
			}
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
		case SDLK_r:
			if (gun) {
				gun->reload();
				hud->mammovalue = gun->m_magAmmo;
				hud->rammovalue = gun->m_reserveAmmo;
				hud->updateAmmo();
			}
			break;
		case SDLK_LSHIFT:
			player->shiftLetGo = SDL_GetTicks();
			player->run = false;
			player->playerSpeed =player->basePlayerSpeed;
			break;
		case SDLK_SPACE:
			player->firing = false;
			break;
		case SDLK_ESCAPE:
			Audio::pauseMusic();
			visibilities::gameVisibility = false;
			visibilities::menuVisibility = true;
			SDL_SetWindowTitle(((Window*)visibilities::windowPTRVOID)->m_Window, "Mafia Gangs | Menu");
		}
	}
	return true;
}