#include "GameManager.h"
Window* GameManager::mainWindow = nullptr;
unsigned int GameManager::framesCap=60;
unsigned int GameManager::framesCount=0;
Uint32 GameManager::iStart;
Uint32 GameManager::lastFrame;
unsigned int GameManager::screenSizeX = 800, GameManager::screenSizeY = 500;

bool GameManager::Initialize()
{
	system("title MAFIA GANG BOOT");
	mainWindow = new Window("Mafia Gangs | Menu", screenSizeX, screenSizeY);
	visibilities::windowPTRVOID = mainWindow;
	mainWindow->setWindowIcon("res/icon.jpg");
	Menu::Initialize(true, screenSizeX, screenSizeY);
	Loading::Initialize(false, screenSizeX, screenSizeY); //add initailized variable to each class so that it only initializes if it has to
	Settings::Initialize(false, screenSizeX, screenSizeY);
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
			//std::cout << "FPS: " << --framesCount;
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
