#include <SDL.h>

#include <algorithm>
#include "Game.h"
#include "Graphics.h"
#include "Input.h"

/*
	Game class holding the Information for running/looping of the Main Game
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphic;
	Input input;
	SDL_Event event;

	this->_player = Sprite(graphic, "Content/Sprites/MyChar.png", 0, 0, 16, 16, 100, 100);

	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Starting the Game Loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0)
					input.keyDownEvent(event);
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
				return;
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
			return;

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME)); //Limiting to 50 FPS

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphic);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	this->_player.draw(graphics, 100, 100);

	graphics.flip();
}

void Game::update(float elapsedTime) {

}