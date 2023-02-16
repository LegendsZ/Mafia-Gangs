#include "Dialog.h"

Rect* Dialog::picture=nullptr;
Rect* Dialog::bkgdDialog=nullptr;
Text* Dialog::text=nullptr;
Button* Dialog::btnOk = nullptr;
unsigned int Dialog::mouseX, Dialog::mouseY;
void(*Dialog::clickEvent)();

Dialog::Dialog(){

}

bool Dialog::draw()
{
	bkgdDialog->draw();
	picture->draw();
	text->display();
	btnOk->draw();
	return true;
}

bool Dialog::pollEvents(SDL_Event& event)
{
	btnOk->pollEvents(event);
	return true;
}

void Dialog::btnOkClickHandler(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (mouseX >= btnOk->getPos()[0] && mouseX <= btnOk->getPos()[0] + btnOk->m_Rect->m_Width && mouseY >= btnOk->getPos()[1] && mouseY <= btnOk->getPos()[1] + btnOk->m_Rect->m_Height) {
			clickEvent();
		}
	}
}