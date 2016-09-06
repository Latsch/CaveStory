#ifndef GAME_H
#define GAME_H

#include "AnimateSprites.h"
class Graphics; //Forward declaration of class Graphics, needed for draw()

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	AnimateSprites _player;
};

#endif GAME_H