#include "SDL.h"
#undef main

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include "GameManager.h"

int main() {
#ifdef WINDOWS
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

    GameManager::Initialize();

#ifdef WINDOWS
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

    GameManager::Run();

#ifdef WINDOWS
    ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

    GameManager::Terminate();
}