#include "AnimateSprites.h"
#include "Graphics.h"
#include "Sprite.h"


AnimateSprites::AnimateSprites() {}

AnimateSprites::AnimateSprites(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY, float timeToUpdate) :
		Sprite(graphics, filePath, sourceX, sourceY , width, height, posX, posY),
		frameIndex(0),
		timeToUpdate(timeToUpdate),
		visible(true),
		currentAnimationOnce(true),
		currentAnimation(""),
		timeElapsed(0)

{}

void AnimateSprites::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector offset) {
	std::vector<SDL_Rect> rectangles;

	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i + x) * width, y , width, height };
		rectangles.push_back(newRect);

	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->offset.insert(std::pair<std::string, Vector>(name, offset));
}

void AnimateSprites::resetAnimation() {

	this->_animations.clear();
	this->offset.clear();
}

void AnimateSprites::playAnimation(std::string name, bool once) {

	this->currentAnimationOnce = once;

	if (currentAnimation != name) {
		this->currentAnimation = name;
		this->frameIndex = 0;
	}
}

void AnimateSprites::setVisible(bool visible) {
	this->visible = visible;
}

void AnimateSprites::stopsAnimation() {
	this->frameIndex = 0;
	this->animationDone(this->currentAnimation);

}

void AnimateSprites::update(int elapsedTime) {
	Sprite::update();

	this->timeElapsed += elapsedTime;

	if (this->timeElapsed > this->timeToUpdate) {
		this->timeElapsed -= this->timeToUpdate;
		if (this->frameIndex < this->_animations[this->currentAnimation].size() - 1) 
		{
			this->frameIndex++;
		}
		else 
		{
			if (this->currentAnimationOnce == true)
			{
				this->setVisible(false);
			}
			this->frameIndex = 0;
			this->animationDone(this->currentAnimation);
		}
	}
}

void AnimateSprites::draw(Graphics &graphics, int x, int y) {

	if (this->visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->offset[this->currentAnimation].x;
		destinationRectangle.y = y + this->offset[this->currentAnimation].y;
		destinationRectangle.h = this->_sourceRect.h + globalVar::SPRITE_SCALE;
		destinationRectangle.w = this->_sourceRect.w + globalVar::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->currentAnimation][this->frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}

}
