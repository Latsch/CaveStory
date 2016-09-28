#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include "globalVar.h"

/*
	Graphics.h implementation
	Holds all information dealing with graphics
*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globalVar::SCREEN_WIDTH, globalVar::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "CaveStory");
};

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
};

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinaionRectangle) {
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinaionRectangle);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}