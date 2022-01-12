#include "Sprite.h"



CSprite::CSprite(SDL_Texture* texture, int width, int height)
{
	this->texture = texture;
	this->width = static_cast<float>( width );
	this->height = static_cast<float>( height );
}

CSprite::~CSprite()
{
	// Note, we don't delete this, as it's a reference, so just set to NULL
	texture = NULL;
}

void CSprite::Render(SDL_Renderer* renderer, float x, float y, float sx, float sy, double angle, bool bCenter, SDL_RendererFlip flip, SDL_Rect rect) const
{
	//Render texture to screen
	if (texture)
	{
		//Set rendering space and render to screen
		float w = width * sx;
		float h = height * sy;

		

		SDL_Rect dRect = { x, y, w, h};
		
		//Set clip rendering dimensions (scale)
		
		SDL_Rect sRect = { 0, 0, width, height};
		
		if (bCenter)
		{
			dRect.x -= dRect.w / 2;
			dRect.y -= dRect.h / 2;
		}


		if (rect.x != -1)
		{
			dRect.x = x;
			dRect.y = y;
			dRect.w = rect.w * sx;
			dRect.h = rect.h * sy;

			sRect.x = rect.x;
			sRect.y = rect.y;
			sRect.w = rect.w;
			sRect.h = rect.h;

			dRect.x -= (dRect.w / 2);
			dRect.y -= (dRect.h / 2);
		}

		
		
		
		//Render to screen
		SDL_RenderCopyEx(renderer, texture, &sRect, &dRect, angle, NULL, flip);
	}
}