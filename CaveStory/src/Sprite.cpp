#include "Sprite.h"
#include "Graphics.h"
#include "globalVar.h"

Sprite::Sprite(){}


Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
	float posX, float posY) :
	_x(posX), _y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	if (_spriteSheet == 0) {
		printf("\n Error: Unable to load image\n");
	}
}

Sprite::~Sprite(){}

void Sprite::draw(Graphics &graphics, int x , int y) {
	SDL_Rect destinationRectangle = { x, y,this->_sourceRect.w * globalVar::SPRITE_SCALE, 
											this->_sourceRect.h * globalVar::SPRITE_SCALE};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update() {

}

