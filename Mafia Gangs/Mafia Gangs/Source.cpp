#include "SDL.h"
#undef main

#pragma once
#include "GameManager.h"

#define ADJUSTMENT_FACTOR 25

int main() {
	GameManager::Initialize();
	GameManager::Run();
	GameManager::Terminate();
}