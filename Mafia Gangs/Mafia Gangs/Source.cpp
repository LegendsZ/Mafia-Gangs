#include "SDL.h"
#undef main


#include "Menu.h"
#pragma once

#define ADJUSTMENT_FACTOR 25

int main() {
	system("title MAFIA GANG BOOT");

	//init vars here
	unsigned int framesCap = 60;
	unsigned int framesCount = 0;
	Uint32 iStart;
	Uint32 lastFrame;
	const unsigned int screenSizeX = 800, screenSizeY = 500;
	SDL_Event* event = new SDL_Event;

	Window* mainWindow = new Window("Mafia Gangs | Menu", screenSizeX, screenSizeY);
	mainWindow->setWindowIcon("res/icon.jpg");
	Menu::Initialize(true, screenSizeX, screenSizeY);
	Menu::btnAnimation = true;
	Loading::Initialize(false, screenSizeX, screenSizeY);

	

	lastFrame = SDL_GetTicks();
	while (!mainWindow->isClosed()) {
		iStart = SDL_GetTicks();


		SDL_ShowWindow(mainWindow->m_Window);
		SDL_PollEvent(event);

		if (Menu::enabled) {
			Menu::draw();
			Menu::pollEvents();
		}
		else if (Loading::enabled) {
			Loading::draw();
		}

		mainWindow->clear();


		framesCount++;
		if (1000 / framesCap > SDL_GetTicks() - iStart) { //to cap frames
			Uint32 toDelay = 1000 / framesCap - (SDL_GetTicks() - iStart);
			SDL_Delay(toDelay);
		}
		if ((SDL_GetTicks() - lastFrame) / 1000.0 >= 1) {
			system("cls");
			std::cout << "Initializing...OK!\n";
			std::cout << "FPS: " << --framesCount;
			framesCount = 0;
			lastFrame = SDL_GetTicks();
		}
	}

	std::cout << "\nTerminating...";
	delete mainWindow;
	std::cout << "OK!\n";
	return 0;
}