#include "GameMode.h"



int GameMode::DEFAULTSCREENX = 800, GameMode::DEFAULTSCREENY = 500;
float GameMode::magnification = 1;
float GameMode::magnificationX = GameMode::magnification;
float GameMode::magnificationY = GameMode::magnification;

unsigned int GameMode::screenSizeX, GameMode::screenSizeY;
unsigned int GameMode::mouseX, GameMode::mouseY;
Rect* GameMode::bkgdGameMode;
Rect* GameMode::title;
Button* GameMode::btnClassic;
Button* GameMode::btnZombies;
Button* GameMode::btnBack;

int GameMode::btnAnimationIncrementor = -1;



bool GameMode::Initialize(bool enabled, unsigned int screenSizeX, unsigned int screenSizeY)
{
	visibilities::gameModeVisibility = enabled;
	GameMode::screenSizeX = screenSizeX;
	GameMode::screenSizeY = screenSizeY;
	GameMode::magnificationX = (GameMode::magnificationX / GameMode::DEFAULTSCREENX) * screenSizeX;
	GameMode::magnificationY = (GameMode::magnificationY / GameMode::DEFAULTSCREENY) * screenSizeY;

	GameMode::title = new Rect(250 * GameMode::magnificationX, 125 * GameMode::magnificationY, 465 * GameMode::magnificationX, 25 * GameMode::magnificationY, "res/gamemodetitle.png");
	GameMode::bkgdGameMode = new Rect(screenSizeX, screenSizeY, 0, 0, "res/bkgdMenu.jpg");

	GameMode::btnClassic = new Button(
		175 * GameMode::magnificationX, 75 * GameMode::magnificationY,
		500 * GameMode::magnificationX,
		175 * GameMode::magnificationY,
		"res/btnClassic.png", GameMode::btnClassicClickEvent);
	GameMode::btnZombies = new Button(
		175 * GameMode::magnificationX, 75 * GameMode::magnificationY,
		500 * GameMode::magnificationX,
		275 * GameMode::magnificationY,
		"res/btnZombies.png", GameMode::btnZombiesClickEvent);
	GameMode::btnBack = new Button(
		175 * GameMode::magnificationX, 75 * GameMode::magnificationY,
		500 * GameMode::magnificationX,
		375 * GameMode::magnificationY,
		"res/btnBack.png", GameMode::btnBackClickEvent);
	return true;
}

void GameMode::btnClassicClickEvent(SDL_Event& event)
{
	//W.I.P
}

void GameMode::btnZombiesClickEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnZombies->getPos()[0] && mouseX <= btnZombies->getPos()[0] + btnZombies->m_Rect->m_Width && mouseY >= btnZombies->getPos()[1] && mouseY <= btnZombies->getPos()[1] + btnZombies->m_Rect->m_Height) {
			SDL_SetWindowTitle(((Window*)visibilities::windowPTRVOID)->m_Window, "Mafia Gangs");
			visibilities::gameModeVisibility = false;
			if (!Game::loaded) {

				//load zombie texture
				Enemy::wT = Rect::getTexture("res/zombiew.png");
				Enemy::aT = Rect::getTexture("res/zombiea.png");
				Enemy::sT = Rect::getTexture("res/zombies.png");
				Enemy::dT = Rect::getTexture("res/zombied.png");

				visibilities::loadingVisibility = true;
				Loading::loader = GameMode::gameLoader;
				SDL_CreateThread(SDL_ThreadFunction(Loading::loader), "game", nullptr);
			}
			else {
				visibilities::gameVisibility = true;
			}
			Audio::resumeMusic();
		}
	}
}

void GameMode::btnBackClickEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnBack->getPos()[0] && mouseX <= btnBack->getPos()[0] + btnBack->m_Rect->m_Width && mouseY >= btnBack->getPos()[1] && mouseY <= btnBack->getPos()[1] + btnBack->m_Rect->m_Height) {
			visibilities::menuVisibility = true;
			visibilities::gameModeVisibility = false;
		}
	}
}

void GameMode::gameLoader()
{
	Game::Initialize(false, screenSizeX, screenSizeY);
	visibilities::gameVisibility = true;
	visibilities::loadingVisibility = false;
}

bool GameMode::pollEvents()
{
	if (!visibilities::gameModeVisibility) {
		return false;
	}
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x <= screenSizeX ? event.motion.x : mouseX;
		mouseY = event.motion.y <= screenSizeY ? event.motion.y : mouseY;
	}
	else {
		btnClassic->pollEvents(event);
		btnZombies->pollEvents(event);
		btnBack->pollEvents(event);
	}
	return true;
}

bool GameMode::draw()
{
	if (visibilities::animations) {
		if (btnClassic->getPos()[0] <= 450 * GameMode::magnificationX) {
			GameMode::btnAnimationIncrementor *= -1;
		}
		else if (btnClassic->getPos()[0] >= 500 * GameMode::magnificationX) {
			GameMode::btnAnimationIncrementor *= -1;
		}
		btnClassic->setPos(btnClassic->getPos()[0] - btnAnimationIncrementor, btnClassic->getPos()[1]);
		btnClassic->m_Rect->m_Width += (2 * btnAnimationIncrementor);
		btnZombies->setPos(btnZombies->getPos()[0] - btnAnimationIncrementor, btnZombies->getPos()[1]);
		btnZombies->m_Rect->m_Width += (2 * btnAnimationIncrementor);
		btnBack->setPos(btnBack->getPos()[0] - btnAnimationIncrementor, btnBack->getPos()[1]);
		btnBack->m_Rect->m_Width += (2 * btnAnimationIncrementor);
	}
	bkgdGameMode->draw();
	title->draw();
	btnClassic->draw();
	btnZombies->draw();
	btnBack->draw();
	return true;
}
