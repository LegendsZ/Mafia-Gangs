#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"
#include "ScreenVisibility.h"

class Settings {
public:
	//static bool enabled;
	static unsigned int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;
	static Rect* bkgdSettings;
	static Text* title;

	static Button* btnBack;
	static bool animations;
	static int btnAnimationIncrementor;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static void btnBackClickEvent(SDL_Event& event);

	static bool pollEvents();
	static bool draw();
private:

};