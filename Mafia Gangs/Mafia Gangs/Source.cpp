#include "SDL.h"
#undef main

#include "GameManager.h"

int main() {
	GameManager::Initialize();
	GameManager::Run();
	GameManager::Terminate();
}