#include "Loading.h"


bool Loading::enabled;
unsigned int Loading::screenSizeX, Loading::screenSizeY;
unsigned int Loading::mouseX, Loading::mouseY;
Rect* Loading::bkgdLoading;

bool Loading::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	Loading::enabled = enabled;
	Loading::screenSizeX = screenSizeX;
	Loading::screenSizeY = screenSizeY;
	Loading::bkgdLoading = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdLoading.jpg");
	return true;
}

bool Loading::draw() {
	if (Loading::enabled) {
		Loading::bkgdLoading->draw();
		return true;
	}
	return false;
}