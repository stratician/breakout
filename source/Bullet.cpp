#include "Bullet.h"
#include "Common.h"

Bullet::Bullet()
{
	type = BULLET_TYPE::DEFAULT;
}

Bullet::~Bullet()
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


bool Bullet::Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int life, OWNER_TYPE ownerType)
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

	this->life = life;
	this->ownerType = ownerType;

	cyc32 = 0;


	playSFX(type);

	return true;
}


void Bullet::Render() const
{
	double sx = 0.3f;
	double sy = 0.3f;
	SDL_Rect rect = { -1, -1, -1, -1 };
	if (type == BULLET_TYPE::RED_FLAME)
	{
		rect.x = (cyc32 >> 3) * 68;
		rect.y = 0;
		rect.w = 68;
		rect.h = 169;
		sx = 0.8f;
		sy = 0.8f;
	}

	// set alpha
	//SDL_SetTextureAlphaMod(texture, 32);

	double angle = 0;
	if (this->vx >= -0.01 && this->vx <= 0.01)
		angle = this->vy > 0 ? 180 : 0;
	else
		angle = -(atan(this->vx / this->vy) * 180 / PI);

	spr->Render(gRenderer, x, y, sx, sy, angle, true, SDL_FLIP_NONE, rect);
}


void Bullet::Process()
{

	this->x += this->vx;
	this->y += this->vy;

	Vec v = { this->vx, this->vy };
	v.normalize();
	
	// Get direction

	this->vx += v.x * 0.1f;
	this->vy += v.y * 0.1f;
	
	cyc32 = (cyc32 + 1) % 32;

	if (life)
	{
		--life;
	}

	

}

int Bullet::getLife() const
{
	return this->life;
}


bool Bullet::ApplyDamage(int damage)
{
	if (life > 0)
	{
		life -= damage;
	}

	if (life < 0)
	{
		life = 0;
	}


	return life > 0;
}

OWNER_TYPE Bullet::getOwnerType() const
{
	return ownerType;
}