#pragma once
#include "Game.h"
#include "Loading.h"

class GameMode {
public:
	//static bool enabled;

	static int DEFAULTSCREENX, DEFAULTSCREENY;
	static float magnification;
	static float magnificationX;
	static float magnificationY;

	static unsigned int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;
	static Rect* bkgdGameMode;
	static Rect* title;

	static Button* btnClassic;
	static Button* btnZombies;
	static Button* btnBack;

	static int btnAnimationIncrementor;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static void btnClassicClickEvent(SDL_Event& event);
	static void btnZombiesClickEvent(SDL_Event& event);
	static void btnBackClickEvent(SDL_Event& event);
	static void gameLoader();

	static bool pollEvents();
	static bool draw();
private:

};