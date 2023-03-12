#include "MissionOne.h"

MissionOne* MissionOne::self = nullptr;
bool MissionOne::startOrContinue()
{
	self = this;
	SDL_Thread* thread = SDL_CreateThread(mainLogic, "missionOne", (void*)NULL);
	return true;
}

int MissionOne::mainLogic(void* nullData)
{
	while (true) { //add bool to class tht can be used to check for thread exit.
		switch ((int)MissionOne::self->completion) {
		case 0:
			if (!self->dialog) {
				self->dialog = new Dialog();
				self->dialog->bkgdDialog = new Rect(500, 250, 0,830,255,0,0,255);
				self->dialog->picture = new Rect(50, 50, 0, 830, 0, 255, 0, 255);
				self->dialog->text = new Text(Window::renderer, "res/comic.ttf", 20, "Welcome to Mafia Gangs!", {0,0,255,255});
				self->dialog->text->setPos(self->dialog->bkgdDialog->getPos()[0] + self->dialog->picture->getPos()[0], self->dialog->bkgdDialog->getPos()[1] + self->dialog->picture->getPos()[1]);
			}

		}
		MissionOne::self->draw();
	}
	return 0;
}

bool MissionOne::reset()
{
	completion = 0;
	return true;
}

bool MissionOne::draw()
{
	if (dialog) {
		dialog->draw();
	}
	return true;
}
