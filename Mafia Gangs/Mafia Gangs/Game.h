#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"
#include "ScreenVisibility.h"
#include "Dialog.h"
#include "HUD.h"
#include "CollisionMap.h"
#include <vector>

struct Player {
public:
	static Rect* player;
	static int x;
	static int y;
	static float playerSpeed;
	static float basePlayerSpeed;
	static float runSpeed;
	static bool run;
	static Uint32 shiftLetGo;
	static bool w;
	static bool a;
	static bool s;
	static bool d;
};

class Game {
public:
	static int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;
	//static Rect* bkgdGame;
	static Rect* bkgdsGame[];
	static float magnification;
	static Player* player;
	static HUD* hud;
	static bool loaded;
	static bool gameLogic();
	static bool Initialize(bool enabled, int screenSizeX, int screenSizeY);
	static bool pollEvents();
	static bool pollPlayerControls(SDL_Event& event);
	static bool draw();
	static Dialog* dialog;
private:

};