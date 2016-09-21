#ifndef LEVEL_H
#define LEVEL_H


#include <string>
#include "globalVar.h"

class Graphics;
struct SDL_Texture;

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

	SDL_Texture* _backgroundTexture;

	/*
		Loads a map
	*/
	void loadMap(std::string mapName, Graphics &graphics);

};


#endif LEVEL_H