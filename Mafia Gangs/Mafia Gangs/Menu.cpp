#include "Menu.h"


//bool Menu::enabled;
unsigned int Menu::screenSizeX, Menu::screenSizeY;
unsigned int Menu::mouseX, Menu::mouseY;
Rect* Menu::bkgdMenu;
Rect* Menu::title;
Button* Menu::btnPlay;
Button* Menu::btnSettings;
Button* Menu::btnExit;

int Menu::btnAnimationIncrementor = -1;

bool Menu::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY) {
	visibilities::menuVisibility= enabled;
	Menu::screenSizeX = screenSizeX;
	Menu::screenSizeY = screenSizeY;
	Menu::bkgdMenu = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdMenu.jpg");
	Menu::title= new Rect(250, 125, 465, 25, "res/menutitle.png");

	Menu::btnPlay = new Button(
		175, 75,
		500,
		175,
		"res/menuBtnPlay.png", Menu::btnPlayClickEvent);
	Menu::btnSettings = new Button(
		175, 75,
		500,
		275,
		"res/menuBtnSettings.png", Menu::btnSettingsClickEvent);
	Menu::btnExit = new Button(
		175, 75,
		500,
		375,
		"res/menuBtnExit.png", Menu::btnExitClickEvent);
	return true;
}

bool Menu::draw() {
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
		btnExit->setPos(btnExit->getPos()[0] - btnAnimationIncrementor, btnExit->getPos()[1]);
		btnExit->m_Rect->m_Width += (2 * btnAnimationIncrementor);
	}


	Menu::bkgdMenu->draw();
	Menu::btnPlay->draw();
	Menu::btnSettings->draw();
	Menu::btnExit->draw();
	Menu::title->draw();
	return true;
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
	else {
		btnPlay->pollEvents(event);
		btnSettings->pollEvents(event);
		btnExit->pollEvents(event);
	}
	
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
			SDL_SetWindowTitle(((Window*)visibilities::windowPTRVOID)->m_Window, "Mafia Gangs");
			visibilities::menuVisibility = false;
			if (!Game::loaded) {
				visibilities::loadingVisibility = true;
				Loading::loader = Menu::gameLoader;
				SDL_CreateThread(SDL_ThreadFunction(Loading::loader), "game", nullptr);
			}
			else {
				visibilities::gameVisibility = true;
			}
		}
	}
}

void Menu::btnSettingsClickEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnSettings->getPos()[0] && mouseX <= btnSettings->getPos()[0] + btnSettings->m_Rect->m_Width && mouseY >= btnSettings->getPos()[1] && mouseY <= btnSettings->getPos()[1] + btnSettings->m_Rect->m_Height) {
			SDL_SetWindowTitle(((Window*)visibilities::windowPTRVOID)->m_Window, "Mafia Gangs | Settings");
			visibilities::settingsVisibility = true;
			visibilities::menuVisibility = false;
		}
	}
}void Menu::btnExitClickEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnExit->getPos()[0] && mouseX <= btnExit->getPos()[0] + btnExit->m_Rect->m_Width && mouseY >= btnExit->getPos()[1] && mouseY <= btnExit->getPos()[1] + btnExit->m_Rect->m_Height) {
			((Window*)visibilities::windowPTRVOID)->close();
		}
	}
}