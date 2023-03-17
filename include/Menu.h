#pragma once
#include <iostream>
#include "Settings.h"
#include "GameMode.h"

class Menu {
public:
	//static bool enabled;

	static int DEFAULTSCREENX, DEFAULTSCREENY;
	static float magnification;
	static float magnificationX;
	static float magnificationY;

	static unsigned int screenSizeX,screenSizeY;
	static unsigned int mouseX, mouseY;
	static Rect* bkgdMenu;
	static Rect* title;

	static Button* btnPlay;
	static Button* btnSettings;
	static Button* btnExit;

	static int btnAnimationIncrementor;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static void btnPlayClickEvent(SDL_Event& event);
	static void btnSettingsClickEvent(SDL_Event& event);
	static void btnExitClickEvent(SDL_Event& event);
	static void gameLoader();

	static bool pollEvents();
	static bool draw();
private:

};