#pragma once
#include <iostream>
#include "Settings.h"
#include "Loading.h"
#include "Game.h"

class Menu {
public:
	//static bool enabled;
	static unsigned int screenSizeX,screenSizeY;
	static unsigned int mouseX, mouseY;
	static Rect* bkgdMenu;
	static Text* title;

	static Button* btnPlay;
	static Button* btnSettings;
	static int btnAnimationIncrementor;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static void btnPlayClickEvent(SDL_Event& event);
	static void btnSettingsClickEvent(SDL_Event& event);
	static void gameLoader();

	static bool pollEvents();
	static bool draw();
private:

};