#ifndef GRAPHCS_H
#define GRAPHICS_H

struct SDL_Window; //Forward declaration with pointers;
struct SDL_Renderer;

#include <SDL.h>
#include <map>
#include <string>

/*
Graphics.h implementation
Holds all information dealing with graphics
*/

class Graphics {
public:
	Graphics();
	~Graphics();

	/*
		Loads an Image into the SpriteSheet Map if it doesnt already exist
		As a result every Image will only be loaded once
		Returns the image from the map regardless of whether or not it was just loaded
	*/
	SDL_Surface* loadImage(const std::string &filePath);


	/*
	Draws Texture/Images to a certain part of the  screen
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/*
		Renders everything to the screen
	*/
	void flip();

	/*
		Clears the screen
	*/
	void clear();

	/*
		Returns the Renderer
	*/
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif GRAPHICS_H