#include "Level.h"
#include "Graphics.h"
#include "globalVar.h"

#include <SDL.h>

Level::Level(){}

Level::~Level(){}

Level::Level(std::string mapName, Vector spawnPoint, Graphics &graphics) :
		_mapName(mapName),
		_spawnPoint(spawnPoint),
		_size(Vector(0,0))
{
	this->loadMap(mapName, graphics);
}


void Level::draw(Graphics &graphics) {
	//Draw the background...
	SDL_Rect sourceRect = {0, 0, 64, 64};
	SDL_Rect destRect;

	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = x * 64 * globalVar::SPRITE_SCALE; // making the background twice as big
			destRect.y = y * 64 * globalVar::SPRITE_SCALE;
			destRect.w = 64 * globalVar::SPRITE_SCALE;
			destRect.h = 64 * globalVar::SPRITE_SCALE;
			graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}

void Level::update(int elapsedTime) {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//Temporary code to load the background
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), 
										graphics.loadImage("Content/Backgrounds/bkBlue.png"));
	this->_size = Vector(1280, 940);
}