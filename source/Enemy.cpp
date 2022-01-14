#include "Enemy.h"
#include "Common.h"
#include "Bullet.h"



Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	
}

bool Enemy::Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int health)
{
	
	Entity::Init((OWNER_TYPE)type, health);
	
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

	this->radius = 30.0f + health;
	this->coolDown = 60 * 3;
	return true;
}


void Enemy::Render()
{

	sx = 0.3f * this->radius / 30.0f;
	sy = 0.3f * this->radius / 30.0f;

	Entity::Render();
	
}


void Enemy::Process(int &nextDirection)
{
	// Process Code

	Entity::Process();

	switch (action)
	{
		case ACTION::AI_LEFT:
			this->vx -= 0.02f * gGameSpeed * (radius / 60.0f);
			break;
		case ACTION::AI_RIGHT:
			this->vx += 0.02f * gGameSpeed * (radius / 60.0f);
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
		nextDirection = (int) ACTION::AI_LEFT;
	}

	if (this->x < 0 + this->width / 2)
	{
		this->x = this->width / 2;
		this->vx = 0.0f;
		nextDirection = (int) ACTION::AI_RIGHT;
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

void Enemy::Fire(double vx, double vy)
{
	Entity::Fire(vx, vy, false);


}

void Enemy::SetAction(ACTION action)
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


