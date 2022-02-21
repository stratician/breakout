#include "Item.h"
#include "Common.h"

Item::Item()
{
	type = ITEM_TYPE::DEFAULT;
}

Item::~Item()
{
	// Free Texture
	if (tex)
	{
		SDL_DestroyTexture(tex);
	}

	if (spr)
	{
		delete spr;
	}
}


bool Item::Init(textureTyp* texureData, ITEM_TYPE type, double x, double y, double vx, double vy)
{
	assert(texureData->tex);

	this->type = type;
	this->texWidth = texureData->width;
	this->texHeight = texureData->height;


	// Create the sprite;
	spr = new CSprite(texureData->tex, texWidth, texHeight);

	this->sx = 0.3f;
	this->sy = 0.3f;

	
	this->width = texWidth * sx;
	this->height = texHeight * sy;

	this->x = x;
	this->y = y;

	this->vx = vx;
	this->vy = vy;

	cyc32 = 0;

	return true;
}


void Item::Render() const
{
	// set alpha
	//SDL_SetTextureAlphaMod(texture, 32);

	double angle = 0;
	if (this->vx >= -0.01 && this->vx <= 0.01)
		angle = this->vy > 0 ? 180 : 0;
	else
		angle = -(atan(this->vx / this->vy) * 180 / PI);

	spr->Render(gRenderer, x, y, sx, sy, angle, true, SDL_FLIP_NONE);
}


void Item::Process()
{

	this->x += this->vx;
	this->y += this->vy;

	Vec v = { this->vx, this->vy };
	v.normalize();
	
	// Get direction

	this->vx = v.x * 2.0f;
	this->vy = v.y * 2.0f;
	
	
	cyc32 = (cyc32 + 1) % 32;

	if (life)
	{
		--life;
	}

	

}

void Item::Destroy()
{
	this->bDestroy = true;
}

bool Item::Destroyed() const
{
	return this->bDestroy;
}

ITEM_TYPE Item::GetType() const
{
	return this->type;
}