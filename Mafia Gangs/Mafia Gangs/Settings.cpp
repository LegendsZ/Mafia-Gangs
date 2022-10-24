#include "Settings.h"


//bool Settings::enabled;
unsigned int Settings::screenSizeX, Settings::screenSizeY;
unsigned int Settings::mouseX, Settings::mouseY;
Rect* Settings::bkgdSettings;
Text* Settings::title;
Button* Settings::btnBack;

bool Settings::animations = false;
int Settings::btnAnimationIncrementor = -1;

bool Settings::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY)
{
	visibilities::settingsVisibility = enabled;
	Settings::screenSizeX = screenSizeX;
	Settings::screenSizeY = screenSizeY;
	Settings::bkgdSettings = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdMenu.jpg");
	Settings::title = new Text(Window::renderer, "res/comic.ttf", 50, "SETTINGS", { 0,225,0,1 });
	Settings::title->setPos(screenSizeX / 2 + 50, 20);

	Settings::btnBack = new Button(
		175, 75,
		500,
		350,
		"res/btnPlay.png", Settings::btnBackClickEvent);
	return true;
}

void Settings::btnBackClickEvent(SDL_Event& event)
{
	if (visibilities::settingsVisibility) {
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (mouseX >= btnBack->getPos()[0] && mouseX <= btnBack->getPos()[0] + btnBack->m_Rect->m_Width && mouseY >= btnBack->getPos()[1] && mouseY <= btnBack->getPos()[1] + btnBack->m_Rect->m_Height) {
				visibilities::menuVisibility = true;
				visibilities::settingsVisibility = false;
			}
		}
	}
}

bool Settings::pollEvents()
{
	if (!visibilities::settingsVisibility) {
		return false;
	}
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x <= screenSizeX ? event.motion.x : mouseX;
		mouseY = event.motion.y <= screenSizeY ? event.motion.y : mouseY;
	}

	btnBack->pollEvents(event);
	return true;
}

bool Settings::draw()
{
	if (visibilities::settingsVisibility) {
		if (animations) {
			if (btnBack->getPos()[0] <= 450) {
				Settings::btnAnimationIncrementor *= -1;
			}
			else if (btnBack->getPos()[0] >= 500) {
				Settings::btnAnimationIncrementor *= -1;
			}
			btnBack->setPos(btnBack->getPos()[0] - btnAnimationIncrementor, btnBack->getPos()[1]);
			btnBack->m_Rect->m_Width += (2 * btnAnimationIncrementor);
		}


		Settings::bkgdSettings->draw();
		Settings::btnBack->draw();
		Settings::title->display();
		return true;
	}
	return false;
}