#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"
#include "ScreenVisibility.h"

struct Player {
public:
	static Rect* player;
	static int playerSpeed;
	static bool w;
	static bool a;
	static bool s;
	static bool d;
};

class Game {
public:
	static unsigned int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;
	static Rect* bkgdGame;
	static Player* player;
	static bool gameLogic();
	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static bool pollEvents();
	static bool pollPlayerControls(SDL_Event& event);
	static bool draw();
private:

};