#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class CSprite
{

private:


protected:
	//Current displayed texture
	SDL_Texture* texture = NULL;
	float width;
	float height;


public:

	CSprite(SDL_Texture* texture, int width, int height);
	virtual ~CSprite();

	
	virtual void Render(SDL_Renderer* renderer, float x, float y, float sx, float sy, double angle = 0.0, bool bCenter = false, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect rect = {-1, -1, -1, -1}) const;


};

