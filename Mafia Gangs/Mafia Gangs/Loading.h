#pragma once
#include <iostream>
#include "Window.h"
#include "Button.h"


class Loading {
public:
	static bool enabled;
	static unsigned int screenSizeX, screenSizeY;
	static unsigned int mouseX, mouseY;

	static Rect* bkgdLoading;

	static bool Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY);
	static bool draw();
private:

};