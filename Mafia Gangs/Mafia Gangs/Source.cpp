#include "SDL.h"
#undef main
#include <iostream>
#include "Window.h"
#include "Button.h"

int main() {
	system("title MAFIA GANG BOOT");

	//std::cout << "Initializing...";
	//init vars here
	const unsigned int screenSizeX = 700, screenSizeY = 500;
	SDL_Event* event = new SDL_Event;
	Window* mainWindow = new Window("Mafia Gangs | Menu", screenSizeX, screenSizeY);
	Rect* bkgdMenu = new Rect(screenSizeX, screenSizeY,0,0,"res/bkgdMenu.jpg");
	Button* btnPlay = new Button(
		new Rect(100, 50, (screenSizeX / 2) - (100 / 2), 50, 255, 255, 255, 0),
		new Text(mainWindow->renderer, "res/comic.ttf", 20, "PLAY", { 0,0,255,1 }),
		nullptr
	);
	Text* title = new Text(mainWindow->renderer, "res/comic.ttf", 10, "MAFIA GANGS", { 255,255,255,1 });
	title->setPos(0, 0);
	//std::cout << "OK!\n";
	//system("pause");
	while (!mainWindow->isClosed()) {
		SDL_ShowWindow(mainWindow->m_Window);

		SDL_PollEvent(event);

		bkgdMenu->draw();
		btnPlay->draw();
		title->display();
		mainWindow->clear();
	}

	std::cout << "\nTerminating...";
	delete mainWindow;
	std::cout << "OK!\n";
	return 0;
}