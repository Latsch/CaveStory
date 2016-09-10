#ifndef GLOBALVAR_H
#define GLOBALVAR_H


/*
	Global Variables
*/

namespace globalVar {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector {
	int x, y;

	Vector() :
		x(0), y(0) {}

	Vector(int x, int y):
		x(x), y(y) {}

	Vector zero() {
		return Vector(0, 0);
	}
};

#endif GLOBALVAR_H