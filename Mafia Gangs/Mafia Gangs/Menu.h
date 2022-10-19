#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"

class Menu {
public:
	static bool enabled;
	static unsigned int screenSizeX,screenSizeY;
	static unsigned int mouseX, mouseY;

	static Rect* bkgdMenu;
	static Text* title;

	static Button* btnPlay;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static void btnPlayClickEvent(SDL_Event& event);

	static bool pollEvents();
	static bool draw();
private:

};