#include "GameManager.h"
Window* GameManager::mainWindow = nullptr;
unsigned int GameManager::framesCap=60;
unsigned int GameManager::framesCount=0;
Uint32 GameManager::iStart;
Uint32 GameManager::lastFrame;
unsigned int GameManager::screenSizeX = 1920, GameManager::screenSizeY = 1080; //1250 x 750

bool GameManager::Initialize()
{
	system("title MAFIA GANG BOOT");
	mainWindow = new Window("Mafia Gangs | Menu", screenSizeX, screenSizeY);
	visibilities::windowPTRVOID = mainWindow;
	mainWindow->setWindowIcon("res/icon.png");

	srand(time(NULL));
	//texture loading is here because it should happen in main thread.
	Player::wT = Rect::getTexture("res/playerw.jpg");
	Player::aT = Rect::getTexture("res/playera.jpg");
	Player::sT = Rect::getTexture("res/players.jpg");
	Player::dT = Rect::getTexture("res/playerd.jpg");
	/*Enemy::wT = Rect::getTexture("res/enemyw.png");
	Enemy::aT = Rect::getTexture("res/enemya.png");
	Enemy::sT = Rect::getTexture("res/enemys.png");
	Enemy::dT = Rect::getTexture("res/enemyd.png");*/
	Enemy::wT = Rect::getTexture("res/zombiew.png");
	Enemy::aT = Rect::getTexture("res/zombiea.png");
	Enemy::sT = Rect::getTexture("res/zombies.png");
	Enemy::dT = Rect::getTexture("res/zombied.png");
	Gun::wT = Rect::getTexture("res/bulletw.png");
	Gun::aT = Rect::getTexture("res/bulleta.png");
	Gun::sT = Rect::getTexture("res/bullets.png");
	Gun::dT = Rect::getTexture("res/bulletd.png");
	CollisionMap::collisionImage = IMG_Load("res/collisionFS.bmp");
	HUD::outside = Rect::getTexture("res/outline.png");
	Bullet::impactTexture = Rect::getTexture("res/m1911_bullet_explosion.png");
	Gun::shootsound = Mix_LoadWAV("res/m1911shoot.mp3");
	Gun::reloadsound = Mix_LoadWAV("res/m1911reload.mp3");
	Game::bkgd = Rect::getTexture("res/bkgdGameFS.jpg"); //res/bkgdGame.jpg
	//Game::bkgd = Rect::getTexture("res/collisionFS.bmp"); //res/bkgdGame.jpg
	Game::bkgdMusic = Mix_LoadMUS("res/zombies.mp3");

	Menu::Initialize(true, screenSizeX, screenSizeY);
	Loading::Initialize(false, screenSizeX, screenSizeY); //add initailized variable to each class so that it only initializes if it has to
	Settings::Initialize(false, screenSizeX, screenSizeY);
	GameMode::Initialize(false, screenSizeX, screenSizeY);

	return true;
}

void GameManager::Run()
{
	lastFrame = SDL_GetTicks();
	while (!mainWindow->isClosed()) {
		iStart = SDL_GetTicks();
		SDL_ShowWindow(mainWindow->m_Window);
		if (visibilities::gameVisibility) {
			Game::draw();
			Game::pollEvents();
		}
		else if (visibilities::menuVisibility) {
			Menu::draw();
			Menu::pollEvents();
		}
		else if (visibilities::loadingVisibility) {
			Loading::draw();
			SDL_Event temp;
			SDL_PollEvent(&temp);
		}
		else if (visibilities::gameModeVisibility) {
			GameMode::draw();
			GameMode::pollEvents();
		}
		else if (visibilities::settingsVisibility) {
			Settings::draw();
			Settings::pollEvents();
		}
		mainWindow->clear();
		framesCount++;
		if (1000 / framesCap > SDL_GetTicks() - iStart) { //to cap frames
			Uint32 toDelay = 1000 / framesCap - (SDL_GetTicks() - iStart);
			SDL_Delay(toDelay);
		}
		if ((SDL_GetTicks() - lastFrame) / 1000.0 >= 1) {
			//system("cls");
			//std::cout << "Initializing...OK!\n";
			//std::cout << "FPS: " << framesCount;
			if (Game::hud) {
				Game::hud->updateFPSCounter(--framesCount);
			}
			framesCount = 0;
			lastFrame = SDL_GetTicks();
		}
	}
}

bool GameManager::Terminate()
{
	std::cout << "\nTerminating...";
	delete mainWindow;
	std::cout << "OK!\n";
	return true;
}
