#include "Tile.h"
#include "Graphics.h"

#include "SDL.h"

Tile::Tile() {};

Tile::Tile(SDL_Texture* tileset, Vector size, Vector tilesetPosition, Vector position) :
			_tileset(tileset),
			_size(size),
			_tilesetPosition(tilesetPosition),
			_position(Vector(position.x * globalVar::SPRITE_SCALE, position.y * globalVar::SPRITE_SCALE))

{}

void Tile::update(int elapsedTime) {}


void Tile::draw(Graphics &graphics) {
	SDL_Rect destRect = { this->_position.x, this->_position.y,
					this->_size.x * globalVar::SPRITE_SCALE, this->_size.y * globalVar::SPRITE_SCALE };

	SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y};

	graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}