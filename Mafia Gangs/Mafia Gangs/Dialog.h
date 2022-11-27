#pragma once
#include "Button.h"

class Dialog {
public:
	static Rect* picture;
	static Rect* bkgdDialog;
	static Text* text;
	static Button* btnOk;
	static bool draw();
	static bool pollEvents(SDL_Event& event);
	static void btnOkClickEvent(SDL_Event& event);
	static unsigned int mouseX, mouseY;
private:
};