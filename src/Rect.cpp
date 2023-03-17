#include "Rect.h"

bool Rect::delTexture = true;

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) :
	m_Width(w), m_Height(h), m_R(r), m_G(g), m_B(b), m_A(a)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
}

Rect::Rect(int w, int h, int x, int y, const std::string& img_path) :
	m_Width(w), m_Height(h), current_img_path(img_path)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
	m_Texture = Rect::getTexture(img_path.c_str());
}

Rect::~Rect()
{
	if (delTexture) {
		SDL_DestroyTexture(m_Texture);
	}
}

void Rect::draw() const
{
	SDL_Rect rect = { m_Pos[0], m_Pos[1], m_Width, m_Height }; //probably should store it rather than keep making new rects
	if (m_Texture) {
		SDL_RenderCopy(Window::renderer, m_Texture, nullptr, &rect);
	}
	else {
		SDL_SetRenderDrawColor(Window::renderer, m_R, m_G, m_B, m_A);
		SDL_RenderFillRect(Window::renderer, &rect);
	}
}


bool Rect::pollEvents()
{
	if (m_Handler == nullptr) {
		return false;
	}
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		m_Handler(event);
	}
	return true;
}

bool Rect::pollEvents(SDL_Event event)
{
	if (m_Handler == nullptr) {
		return false;
	}
	m_Handler(event);
	return true;
}

int* Rect::getPos()
{
	return m_Pos;
}

bool Rect::setPos(int x, int y)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
	return true;
}

bool Rect::setDisplacement(int x, int y)
{
	m_Pos[0] += x;
	m_Pos[1] += y;
	return true;
}

bool Rect::changeImage(std::string& img_path)
{
	current_img_path = img_path;
	SDL_DestroyTexture(m_Texture);
	m_Texture = Rect::getTexture(img_path.c_str());
	return true;
}

SDL_Texture* Rect::getTexture(std::string img_path)
{
	SDL_Surface* surface = IMG_Load(img_path.c_str());
	if (!surface) {
		std::cerr << "Failed to create surface!\n";
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create texture!\n";
		return nullptr;
	}
	SDL_FreeSurface(surface);
	return texture;
}
