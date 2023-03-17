#pragma once
#include "Button.h"

class Dialog {
public:
	Dialog();
	static Rect* picture;
	static Rect* bkgdDialog;
	static Text* text;
	static Button* btnOk;
	static void(*clickEvent)();
	static bool draw();
	static bool pollEvents(SDL_Event& event);
	static void btnOkClickHandler(SDL_Event& event);
	static unsigned int mouseX, mouseY;
private:
};