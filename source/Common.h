#pragma once

#include <assert.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "BulletCtrl.h"


extern SDL_Renderer* gRenderer;
extern BulletCtrl* bulletCtrl;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


extern bool KEY_RIGHT;
extern bool KEY_LEFT;
extern bool KEY_FIRE;
extern bool KEY_FIRE_ALT;

extern double PI;

extern double gGameSpeed;

extern bool bAlive;
extern int gLevel;

extern void playSFX(int type);

SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path, int& width, int& height);



struct Vec {
	double x;
	double y;
	double length2() {
		return x * x + y * y;
	}

	double length() {
		return sqrt(length2());
	}

	void normalize() {
		const double len = length();
		x /= len;
		y /= len;
	}
};


struct textureTyp {
	SDL_Texture* tex;
	int width;
	int height;
};
