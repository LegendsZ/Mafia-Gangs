#include "Loading.h"


//bool Loading::enabled;
unsigned int Loading::screenSizeX, Loading::screenSizeY;
unsigned int Loading::mouseX, Loading::mouseY;
void(*Loading::loader);

Rect* Loading::bkgdLoadingOne;
Rect* Loading::bkgdLoadingTwo;

bool Loading::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	visibilities::loadingVisibility = enabled;
	Loading::screenSizeX = screenSizeX;
	Loading::screenSizeY = screenSizeY;
	Loading::bkgdLoadingOne = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdLoading.jpg");
	if (visibilities::animations) {
		Loading::bkgdLoadingTwo = new Rect(screenSizeX, screenSizeY, 0, -((int)screenSizeY), "res/bkgdLoading.jpg");
	}
	return true;
}

bool Loading::draw() {
	Loading::bkgdLoadingOne->draw();
	if (bkgdLoadingTwo != nullptr && visibilities::animations) {
		//animation logic
		Loading::bkgdLoadingOne->setDisplacement(0, 1);
		Loading::bkgdLoadingTwo->setDisplacement(0, 1);
		if (bkgdLoadingOne->getPos()[1] == 0) {
			Loading::bkgdLoadingTwo->setPos(0, -Loading::bkgdLoadingTwo->m_Height);
		}
		else if (bkgdLoadingTwo->getPos()[1] == 0) {
			Loading::bkgdLoadingOne->setPos(0, -Loading::bkgdLoadingOne->m_Height);
		}

		Loading::bkgdLoadingTwo->draw();
	}
	return true;
}


bool Loading::pollEvents()
{
	if (!visibilities::loadingVisibility) {
		return false;
	}
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x <= screenSizeX ? event.motion.x : mouseX;
		mouseY = event.motion.y <= screenSizeY ? event.motion.y : mouseY;
	}
	return true;
}
