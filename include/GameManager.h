#pragma once
#include "Menu.h"

class GameManager {
public:
	static Window* mainWindow;
	static unsigned int framesCap;
	static unsigned int framesCount;
	static uint32_t iStart;
	static uint32_t lastFrame;
	//static unsigned int screenSizeX = 800, screenSizeY = 500;
	static unsigned int screenSizeX ,screenSizeY;
	static bool Initialize();
	static void Run();
	static bool Terminate();
private:
};
