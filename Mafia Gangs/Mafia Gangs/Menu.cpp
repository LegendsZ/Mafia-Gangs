#include "Menu.h"


//bool Menu::enabled;
unsigned int Menu::screenSizeX, Menu::screenSizeY;
unsigned int Menu::mouseX, Menu::mouseY;
Rect* Menu::bkgdMenu;
Text* Menu::title;
Button* Menu::btnPlay;
Button* Menu::btnSettings;

int Menu::btnAnimationIncrementor = -1;

bool Menu::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	visibilities::menuVisibility= enabled;
	Menu::screenSizeX = screenSizeX;
	Menu::screenSizeY = screenSizeY;
	Menu::bkgdMenu = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdMenu.jpg");
	Menu::title = new Text(Window::renderer, "res/comic.ttf", 50, "MAFIA GANGS", { 0,225,0,1 });
	Menu::title->setPos(screenSizeX / 2, 20);

	Menu::btnPlay = new Button(
		175, 75,
		500,
		125,
		"res/btnPlay.png", Menu::btnPlayClickEvent);
	Menu::btnSettings = new Button(
		175, 75,
		500,
		225,
		"res/btnPlay.png", Menu::btnSettingsClickEvent);
	return true;
}

bool Menu::draw() {
	if (visibilities::menuVisibility) {
		if (visibilities::animations) {
			if (btnPlay->getPos()[0] <= 450) {
				Menu::btnAnimationIncrementor *= -1;
			}
			else if (btnPlay->getPos()[0] >= 500) {
				Menu::btnAnimationIncrementor *= -1;
			}
			btnPlay->setPos(btnPlay->getPos()[0] - btnAnimationIncrementor, btnPlay->getPos()[1]);
			btnPlay->m_Rect->m_Width += (2 * btnAnimationIncrementor);
			btnSettings->setPos(btnSettings->getPos()[0] - btnAnimationIncrementor, btnSettings->getPos()[1]);
			btnSettings->m_Rect->m_Width += (2 * btnAnimationIncrementor);
		}


		Menu::bkgdMenu->draw();
		Menu::btnPlay->draw();
		Menu::btnSettings->draw();
		Menu::title->display();
		return true;
	}
	return false;
}

bool Menu::pollEvents()
{
	if (!visibilities::menuVisibility) {
		return false;
	}
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x <= screenSizeX ? event.motion.x : mouseX;
		mouseY = event.motion.y <= screenSizeY ? event.motion.y : mouseY;
	}

	btnPlay->pollEvents(event);
	btnSettings->pollEvents(event);
	return true;
}

void Menu::gameLoader() {
	Game::Initialize(false, screenSizeX,screenSizeY);
	visibilities::gameVisibility = true;
	visibilities::loadingVisibility= false;
}
void Menu::btnPlayClickEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnPlay->getPos()[0] && mouseX <= btnPlay->getPos()[0] + btnPlay->m_Rect->m_Width && mouseY >= btnPlay->getPos()[1] && mouseY <= btnPlay->getPos()[1] + btnPlay->m_Rect->m_Height) {
			visibilities::loadingVisibility = true;
			visibilities::menuVisibility = false;
			Loading::loader = Menu::gameLoader;
			SDL_CreateThread(SDL_ThreadFunction(Loading::loader), "game", nullptr);
		}
	}
}

void Menu::btnSettingsClickEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnSettings->getPos()[0] && mouseX <= btnSettings->getPos()[0] + btnSettings->m_Rect->m_Width && mouseY >= btnSettings->getPos()[1] && mouseY <= btnSettings->getPos()[1] + btnSettings->m_Rect->m_Height) {
			visibilities::settingsVisibility = true;
			visibilities::menuVisibility = false;
		}
	}
}