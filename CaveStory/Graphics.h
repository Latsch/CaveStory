#ifndef GRAPHCS_H
#define GRAPHICS_H

struct SDL_Window; //Forward declaration with pointers;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

#endif GRAPHICS_H