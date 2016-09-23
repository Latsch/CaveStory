#ifndef LEVEL_H
#define LEVEL_H


#include <string>
#include <vector>

#include "globalVar.h"
#include "Tile.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {

public:

	Level();

	Level(std::string mapName, Vector spawnpoint, Graphics &graphics);

	~Level();

	void update(int elapsedTime);

	void draw(Graphics &graphics);


private:
	std::string _mapName;
	Vector _spawnPoint;

	Vector _size;
	Vector _tilesize;


	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	//std::vector<SDL_Rect>

	/*
		Loads a map
	*/
	void loadMap(std::string mapName, Graphics &graphics);

};

//Tileset structure
struct Tileset {
	SDL_Texture* Texture;
	int firstGid;

	Tileset() {
		firstGid = -1;
	}

	Tileset(SDL_Texture* Texture, int firstGid) {
		this->Texture = Texture;
		this->firstGid = firstGid;
	}

};

#endif LEVEL_H