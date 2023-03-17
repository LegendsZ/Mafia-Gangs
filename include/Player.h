#pragma once
struct Player {
public:
	static Rect* player;
	static int x;
	static int y;
	static float playerSpeed;
	static float basePlayerSpeed;
	static float runSpeed;
	static bool run;
	static bool firing;
	static Uint32 shiftLetGo;
	static bool w;
	static bool a;
	static bool s;
	static bool d;
	static SDL_Texture* wT;
	static SDL_Texture* aT;
	static SDL_Texture* sT;
	static SDL_Texture* dT;
};