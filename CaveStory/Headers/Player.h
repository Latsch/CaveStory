#ifndef PLAYER_H
#define PLAYER_H

#include "AnimateSprites.h"
#include "globalVar.h"

class Graphics;

class Player : public AnimateSprites {

public:
	Player();

	/*
		Constructor with starting positions x and y
	*/
	Player(Graphics &graphics, float x, float y);


	/*
		Draws the player to the screen
	*/
	void draw(Graphics &graphics);

	/*
		Updates the sprites
	*/
	void update(float elapsedTime);

	/*
		Moves the player Left/Right by -dx/dx
	*/
	void moveLeft();
	void moveRight();
	
	/*
		Stops movement 
	*/
	void stopMoving();

	/*
	Logic that happens when an animation stops
	*/
	virtual void animationDone(std::string currentAnimation);

	/*
	Required function that sets up all animation for a sprite
	*/
	virtual void setupAnimation();
private:

	float _dx, _dy; //Change in delta X/Y directions

	Direction _facing;

};
#endif PLAYER_H
