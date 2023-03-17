#include "SDL.h"
#undef main
#include <windows.h>
#include "GameManager.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	GameManager::Initialize();
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	GameManager::Run();
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	GameManager::Terminate();
}