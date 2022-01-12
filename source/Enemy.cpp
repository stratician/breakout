#include "Enemy.h"
#include "Common.h"
#include "Bullet.h"



Enemy::Enemy()
{

}

Enemy::~Enemy()
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

bool Enemy::Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int life)
{
	assert(texureData->tex);

	this->ownerType = OWNER_TYPE::OWNER_AI;
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
	this->radius = 30.0f + life;
	this->coolDown = 60 * 3;
	return true;
}

void Enemy::SetWeapon(const int type)
{
	Player::SetWeapon(type);
	
}


void Enemy::Render()
{

	double sx = 0.3f * this->radius / 30.0f;
	double sy = 0.3f * this->radius / 30.0f;
	spr->Render(gRenderer, x, y, sx, sy, 0, true);
}


void Enemy::Process(int &nextDirection)
{
	// Process Code

	Player::Process();

	switch (action)
	{
		case ACTION::AI_LEFT:
			this->vx -= 0.02f * gGameSpeed * (radius / 30.0f);
			break;
		case ACTION::AI_RIGHT:
			this->vx += 0.02f * gGameSpeed * (radius / 30.0f);
			break;
		case ACTION::AI_FIRE:
			// Fire(0.0f, 10.0f);
			break;
	}
	
	this->vx *= 0.96f;
	this->vy *= 0.96f;

	this->x += this->vx;
	this->y += this->vy;

	if (this->x > SCREEN_WIDTH - this->width / 2)
	{
		this->x = SCREEN_WIDTH - this->width / 2;
		this->vx = 0.0f;
		nextDirection = ACTION::AI_LEFT;
	}

	if (this->x < 0 + this->width / 2)
	{
		this->x = this->width / 2;
		this->vx = 0.0f;
		nextDirection = ACTION::AI_RIGHT;
	}

	switch (type)
	{
	case 0: // Default
		if (!coolDown)
		{
			if (rand() % 240 == 0)
			{
				Fire(0.0f, 4.0f);
				coolDown = 60 * 5;
			}
		}
		break;

	case 1: // Boss
		if (!coolDown)
		{
			if (rand() % 90 == 0)
			{
				for (int i = 0; i < 7; ++i)
				{
					Fire(-1.0f + (double)(i) * 0.3f, 3.0f);
				}
				coolDown = 60 * 2;
			}

			
		}
		break;
	}
}

double Enemy::getX() const
{
	return this->x;
}

double Enemy::getY() const
{
	return this->y;
}

void Enemy::Fire(double vx, double vy)
{
	Player::Fire(vx, vy, false);


}

void Enemy::SetAction(int action)
{
	this->action = action;

	this->vx = 0.0f;
	this->vy = 0.0f;
}

void Enemy::ApplyThrust(Vec dir)
{
	this->vx += dir.x;
	this->vy += dir.y;

	
}


