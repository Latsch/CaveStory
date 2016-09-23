#ifndef TILE_H
#define TILE_H


#include "globalVar.h"

struct SDL_Texture;
class Graphics;

class Tile {

public:
	Tile();
	Tile(SDL_Texture* tileset, Vector size, Vector tilesetPosition, Vector position);
	void update(int elapsedTime);
	void draw(Graphics &graphics);
private:
	SDL_Texture* _tileset;
	Vector _size;
	Vector _tilesetPosition;
	Vector _position;


};


#endif TILE_H