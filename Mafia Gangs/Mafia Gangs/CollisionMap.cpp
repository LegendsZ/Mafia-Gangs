#include "CollisionMap.h"

SDL_Surface* CollisionMap::collisionImage = nullptr;
Divided* CollisionMap::map = nullptr;
unsigned int CollisionMap::screenSizeX;
unsigned int CollisionMap::screenSizeY;

bool CollisionMap::makeMap(int w, int h, int magX, int magY) //seems oudated - no use for now.
{
	if (!collisionImage) {
		std::cout << "Error creating collision image surface!\n";
		return false;
	}
	/*if (magX * collisionImage->w != w || magY * collisionImage->h != h) {
		std::cout << "Error - magnification values are invalid!";
		return false;
	}*/
	CollisionMap::screenSizeX = w;
	CollisionMap::screenSizeY = h;
	int size = w * h / 8;
	map = new Divided[size];
	int sizetemp = collisionImage->w * collisionImage->h / 8;
	if (sizetemp != (float)collisionImage->w * collisionImage->h / 8) {
		sizetemp++;
	}
	Divided* maptemp = new Divided[sizetemp];

	Uint32 pixel;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	unsigned char eight[] = { 0,0,0,0,0,0,0,0 };
	int x = 0, y = 0;
	int max = collisionImage->w * collisionImage->h;
	int pitchdiv = collisionImage->pitch / 4;
	SDL_LockSurface(collisionImage);
	for (int i = 0; i < sizetemp; i++) {
		for (int j = 0; j < 8; j++) {
			if (x * y == max) {
				break;
			}
			pixel = ((Uint32*)(collisionImage->pixels))[y * pitchdiv + (x++)];
			//(uint32_t*)(((char*)collisionImage->pixels) + (y *(collisionImage->pitch))+(x++));
			if (x == collisionImage->w) {
				//std::cout << "\n";
				x = 0;
				y++;
			}
			SDL_GetRGBA(pixel, collisionImage->format, &r, &g, &b,&a);
			eight[j] = r == 0 && g == 0 && b == 0;
			if (r == 0 && g == 0 && b == 0) {
				//std::cout << "*";
			}
		}
		maptemp[i] = { eight[0],eight[1],eight[2],eight[3],eight[4],eight[5],eight[6],eight[7]};
		//std::cout << (eight[0] == 1 ? "x" : " ") << (eight[1] == 1 ? "x" : " ") << (eight[2] == 1 ? "x" : " ") << (eight[3] == 1 ? "x" : " ") << (eight[4] == 1 ? "x" : " ") << (eight[5] == 1 ? "x" : " ")<< (eight[6] == 1 ? "x" : " ")<< (eight[7] == 1 ? "x" : " ");
	}
	SDL_UnlockSurface(collisionImage);

	//scaling part below
	if (magX == 1 && magY == 1) {
		delete[] map;
		map = maptemp;
		return true;
	}
	//expand to realmap
	unsigned char eightSpare[8];
	int eightSpareIndex = 0;
	int mapIndex = 0;
	if (magX > 1) { //horizontal expansion
		for (int i = 0; i < sizetemp; i++) {
			eight[0] = maptemp[i].b1;
			eight[1] = maptemp[i].b2;
			eight[2] = maptemp[i].b3;
			eight[3] = maptemp[i].b4;
			eight[4] = maptemp[i].b5;
			eight[5] = maptemp[i].b6;
			eight[6] = maptemp[i].b7;
			eight[7] = maptemp[i].b8;

			for (int k = 0; k < 8; k++) {
				for (int j = 0; j < magX; j++) {
					eightSpare[eightSpareIndex++] = eight[k];
				}
				if (eightSpareIndex == 8) {
					map[mapIndex++] = { eightSpare[0],eightSpare[1],eightSpare[2],eightSpare[3],eightSpare[4],eightSpare[5],eightSpare[6],eightSpare[7] };
					eightSpareIndex = 0;
				}
			}
		}
	}
	

	delete[] maptemp;
	return true;
}

bool CollisionMap::checkCollision(int w, int h, int x, int y) //instead of checking all 4 coords, maybe only check the one that is possible (by movement)
{
	//old collider;
	if (x >= (int)CollisionMap::screenSizeX) {
		x = (x % (int)CollisionMap::screenSizeX); //times magnification?
	}
	if (y>= (int)CollisionMap::screenSizeY) {
		y = (y % (int)CollisionMap::screenSizeY); 
	}
	if (x < 0) {
		while (x < 0) {
			x += (int)CollisionMap::screenSizeX;
		}
	}
	if (y < 0) {
		while (y < 0) {
			y += (int)CollisionMap::screenSizeY;
		}
	}
	int blval = y + h;
	if (blval >= (int)CollisionMap::screenSizeY) {
		blval = blval - (int)CollisionMap::screenSizeY;
	}
	int pitchdiv = collisionImage->pitch / 4;
	Uint32 tl = ((Uint32*)(collisionImage->pixels))[y * pitchdiv + (x)];
	Uint32 tr = ((Uint32*)(collisionImage->pixels))[y * pitchdiv + (x+w)];
	Uint32 bl = ((Uint32*)(collisionImage->pixels))[(blval) *pitchdiv + (x)];
	Uint32 br = ((Uint32*)(collisionImage->pixels))[(blval) *pitchdiv + (x+w)];
	Uint8 r;
	Uint8 g;
	Uint8 b;
	SDL_GetRGB(tl , collisionImage->format, &r, &g, &b);
	if (r == 0 && g==0 && b==0) {
		return false;
	}
	SDL_GetRGB(tr, collisionImage->format, &r, &g, &b);
	if (r == 0 && g == 0 && b == 0) {
		return false;
	}
	SDL_GetRGB(bl, collisionImage->format, &r, &g, &b);
	if (r == 0 && g == 0 && b == 0) {
		return false;
	}
	SDL_GetRGB(br, collisionImage->format, &r, &g, &b);
	if (r == 0 && g == 0 && b == 0) {
		return false;
	}
	return true;

	//new collider
	/*if (x >= (int)CollisionMap::screenSizeX) {
		x = (x % (int)CollisionMap::screenSizeX); //times magnification?
	}
	if (y >= (int)CollisionMap::screenSizeY) {
		y = (y % (int)CollisionMap::screenSizeY);
	}
	if (x < 0) {
		while (x < 0) {
			x += (int)CollisionMap::screenSizeX;
		}
	}
	if (y < 0) {
		while (y < 0) {
			y += (int)CollisionMap::screenSizeY;
		}
	}
	int blval = y + h;
	if (blval >= (int)CollisionMap::screenSizeY) {
		blval = blval - (int)CollisionMap::screenSizeY;
	}
	int indextl = ((CollisionMap::screenSizeX * y + x) / 8);
	char offsettl = (CollisionMap::screenSizeX * y + x) % 8;
	Divided tl = CollisionMap::map[indextl];

	int indextr = ((CollisionMap::screenSizeX * y + x + w) / 8);
	char offsettr = (CollisionMap::screenSizeX * y + x + w) % 8;
	Divided tr = CollisionMap::map[indextr];

	int indexbl = ((CollisionMap::screenSizeX * (blval) + x) / 8);
	char offsetbl = (CollisionMap::screenSizeX * (blval) + x) % 8;
	Divided bl = CollisionMap::map[indexbl];

	int indexbr = ((CollisionMap::screenSizeX * (blval) + x + w) / 8);
	char offsetbr = (CollisionMap::screenSizeX * (blval) + x + w) % 8;
	Divided br = CollisionMap::map[indexbr];

	return helper(tl, offsettl) && helper(tr, offsettr) && helper(bl, offsetbl) && helper(br, offsetbr);*/
}

bool CollisionMap::helper(Divided div, char offset)
{
	switch (offset) {
	case 1:
		if (div.b1 == 1) {
			return false;
		}
		break;
	case 2:
		if (div.b2 == 1) {
			return false;
		}
		break;
	case 3:
		if (div.b3 == 1) {
			return false;
		}
		break;
	case 4:
		if (div.b4 == 1) {
			return false;
		}
		break;
	case 5:
		if (div.b5 == 1) {
			return false;
		}
		break;
	case 6:
		if (div.b6 == 1) {
			return false;
		}
		break;
	case 7:
		if (div.b7 == 1) {
			return false;
		}
		break;
	case 0:
		if (div.b8 == 1) {
			return false;
		}
		break;
	}
	return true;
}
