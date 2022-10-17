#include "SDL.h"
#undef main
#include <iostream>
#include "Window.h"
#include "Rect.h"

int main() {
	system("title MAFIA GANG BOOT");

	//std::cout << "Initializing...";
	//init vars here
	const unsigned int screenSizeX = 500, screenSizeY = 500;
	Window* mainWindow = new Window("Mafia Gangs | Menu", screenSizeX, screenSizeY);
	Rect* bkgdMenu = new Rect(screenSizeX, screenSizeY,0,0,50,50,50,1);
	//std::cout << "OK!\n";
	//system("pause");
	while (!mainWindow->isClosed()) {
		SDL_ShowWindow(mainWindow->m_Window);
		bkgdMenu->draw();
		mainWindow->clear();
	}

	std::cout << "\nTerminating...";
	delete mainWindow;
	std::cout << "OK!\n";
	return 0;
}