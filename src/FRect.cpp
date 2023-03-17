#include "FRect.h"

bool FRect::delTexture = true;

FRect::FRect(float w, float h, float x, float y, int r, int g, int b, int a) :
	m_Width(w), m_Height(h), m_R(r), m_G(g), m_B(b), m_A(a)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
}

FRect::FRect(float w, float h, float x, float y, const std::string& img_path) :
	m_Width(w), m_Height(h), current_img_path(img_path)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
	m_Texture = FRect::getTexture(img_path.c_str());
}

FRect::~FRect()
{
	if (delTexture) {
		SDL_DestroyTexture(m_Texture);
	}
}

void FRect::draw() const
{
	SDL_FRect rect = { m_Pos[0], m_Pos[1], m_Width, m_Height }; //probably should store it rather than keep making new rects
	if (m_Texture) {
		SDL_RenderCopyF(Window::renderer, m_Texture, nullptr, &rect);
	}
	else {
		SDL_SetRenderDrawColor(Window::renderer, m_R, m_G, m_B, m_A);
		SDL_RenderFillRectF(Window::renderer, &rect);
	}
}


bool FRect::pollEvents()
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

bool FRect::pollEvents(SDL_Event event)
{
	if (m_Handler == nullptr) {
		return false;
	}
	m_Handler(event);
	return true;
}

float* FRect::getPos()
{
	return m_Pos;
}

bool FRect::setPos(float x, float y)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
	return true;
}

bool FRect::setDisplacement(float x, float y)
{
	m_Pos[0] += x;
	m_Pos[1] += y;
	return true;
}

bool FRect::changeImage(std::string& img_path)
{
	current_img_path = img_path;
	SDL_DestroyTexture(m_Texture);
	m_Texture = FRect::getTexture(img_path.c_str());
	return true;
}

SDL_Texture* FRect::getTexture(std::string img_path)
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