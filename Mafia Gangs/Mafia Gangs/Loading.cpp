#include "Loading.h"


bool Loading::enabled;
unsigned int Loading::screenSizeX, Loading::screenSizeY;
unsigned int Loading::mouseX, Loading::mouseY;
Rect* Loading::bkgdLoadingOne;

bool Loading::bkgdAnimation = false;
Rect* Loading::bkgdLoadingTwo;

bool Loading::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	Loading::enabled = enabled;
	Loading::screenSizeX = screenSizeX;
	Loading::screenSizeY = screenSizeY;
	Loading::bkgdLoadingOne = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdLoading.jpg");
	if (bkgdAnimation) {
		Loading::bkgdLoadingTwo = new Rect(screenSizeX, screenSizeY, 0, -((int)screenSizeY), "res/bkgdLoading.jpg");
	}
	return true;
}

bool Loading::StartAnimation()
{
	if (Loading::bkgdAnimation == true) {
		return false;
	}
	Loading::bkgdLoadingTwo = new Rect(screenSizeX, screenSizeY, 0, -((int)screenSizeY), "res/bkgdLoading.jpg");
	Loading::bkgdAnimation = true;
	return true;
}

bool Loading::StopAnimation()
{
	delete Loading::bkgdLoadingTwo;
	Loading::bkgdAnimation = false;
	return true;
}

bool Loading::draw() {
	if (Loading::enabled) {
		Loading::bkgdLoadingOne->draw();
		if (bkgdLoadingTwo != nullptr && bkgdAnimation) {
			//animation logic
			Loading::bkgdLoadingOne->setDisplacement(0, 1);
			Loading::bkgdLoadingTwo->setDisplacement(0, 1);
			if (bkgdLoadingOne->getPos()[1] == 0) {
				Loading::bkgdLoadingTwo->setPos(0, -Loading::bkgdLoadingTwo->m_Height);
			}else if (bkgdLoadingTwo->getPos()[1] == 0) {
				Loading::bkgdLoadingOne->setPos(0, -Loading::bkgdLoadingOne->m_Height);
			}

			Loading::bkgdLoadingTwo->draw();
		}
		return true;
	}
	return false;
}

bool Loading::pollEvents()
{
	if (!enabled) {
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
