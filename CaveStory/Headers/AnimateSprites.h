#ifndef ANIMATE_SPRITES_H
#define ANIMATE_SPRITES_H


#include <map>
#include <string>
#include <vector>

#include "Sprite.h"
#include "globalVar.h"

class Graphics;

/*
	AnimateSprites class which holds logic for Animating all Sprites
*/

class AnimateSprites : public Sprite {
public:
	AnimateSprites();
	AnimateSprites(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY, float timeToUpdate);

	/*
		Plays the animation provided its not already playing
		Default only once, flag true for longer loop
	*/
	void playAnimation(std::string animation, bool once = false);

		/*
			Updates the animated Sprites
		*/
	void update(int elapsedTime);


		/*
			Draws sprite to screen
		*/
	void draw(Graphics &grahpics, int x, int y);

	/*
		Required function that sets up all animation for a sprite
	*/
	virtual void setupAnimation();

protected:
	double timeToUpdate;
	bool currentAnimationOnce;
	std::string currentAnimation;


	/*
		Adds animations to the map of animations for the sprites
	*/
	void addAnimation(int frames, int x, int y, std::string name, int widht, int height, Vector offset);


	/*
		Resets all animations associated with the sprite
	*/
	void resetAnimation();


	/*
		Stops the current animation
	*/
	void stopsAnimation();


	/*
		Changes visibility of the animated sprite
	*/
	void setVisible(bool visible);

	/*
		Logic that happens when an animation stops
	*/
	virtual void animationDone(std::string currentAnimation);
private:

	std::map<std::string, std::vector<SDL_Rect> > _animations;
	std::map<std::string, Vector> offset;

	int frameIndex;
	double timeElapsed;
	bool visible;

};

#endif ANIMATE_SPRITES_H