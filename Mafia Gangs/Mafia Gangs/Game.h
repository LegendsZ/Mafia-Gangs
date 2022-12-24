#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"
#include "ScreenVisibility.h"
#include "Dialog.h"
#include "HUD.h"
#include "Player.h"
#include "Enemy.h"
#include "Gun.h"
#include "CollisionMap.h"
#include <vector>



class Game {
public:
	static int DEFAULTSCREENX, DEFAULTSCREENY;
	static int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;
	//static Rect* bkgdGame;
	static Rect* bkgdsGame[];
	static float magnification;
	static float magnificationX;
	static float magnificationY;
	static Player* player;
	static std::vector<Enemy*> enemies;
	static unsigned int enemiesSpawn;
	static HUD* hud;
	static bool loaded;
	static bool gameLogic();
	static bool Initialize(bool enabled, int screenSizeX, int screenSizeY);
	static bool spawnEnemies(int range,int count);
	static bool Reset();
	static bool pollEvents();
	static bool pollPlayerControls(SDL_Event& event);
	static bool draw();
	static Dialog* dialog;
	static SDL_Texture* bkgd;
	static Mix_Music* bkgdMusic;
private:

};