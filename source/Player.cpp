#include "Player.h"
#include "Common.h"
#include "Bullet.h"




Player::Player()
{

}

Player::~Player()
{
	
}


bool Player::Init(OWNER_TYPE ownerType, int life)
{
	Entity::Init(ownerType, life);

	radius = 60.0f; // Default
		
	//Load PNG texture
	tex = loadTexture(gRenderer, "assets/images/ship.png", texWidth, texHeight);
	if (tex == NULL)
	{
		printf("Failed to load player image!\n");
		return false;
	}


	// Create the sprite;

	spr = new CSprite(tex, texWidth, texHeight);

	this->sx = 0.3f;
	this->sy = 0.3f;

	
	this->width = texWidth * sx;
	this->height = texHeight * sy;

	

	this->vx = 0.1f;


	Respawn(this->x = SCREEN_WIDTH / 2, SCREEN_HEIGHT - this->height / 2);

	SetWeapon(WEAPON_TYPE::WEAPON_DEFAULT);

	

	return true;
}



void Player::Render()
{
	Entity::Render();
}


void Player::ProcessInput()
{
	// Process Code
	if (KEY_RIGHT)
	{
		this->vx += 0.5f;
	}

	if (KEY_LEFT)
	{
		this->vx -= 0.5f;
	}

	if (KEY_FIRE)
	{
		weaponType = WEAPON_TYPE::WEAPON_DEFAULT;
		Fire(0.0f, -10.0f);
	}

	if (KEY_FIRE_ALT)
	{
		weaponType = WEAPON_TYPE::WEAPON_RED_FLAME;

		if (!coolDown)
		{
			Fire(0.0f, -10.0f);
			coolDown = 0;
			Fire(-2.0f, -9.0f);
			coolDown = 0;
			Fire(2.0f, -9.0f);
		}
	}


	this->vx *= 0.95f;

	this->x += this->vx;
	this->y += this->vy;

	if (this->x > SCREEN_WIDTH - this->width / 2)
	{
		this->x = SCREEN_WIDTH - this->width / 2;
		this->vx = 0.0f;
	}

	if (this->x < 0 + this->width / 2)
	{
		this->x = this->width / 2;
		this->vx = 0.0f;
	}


	

}

void Player::Process()
{
	
	Entity::Process();

	if (coolDown)
	{
		--coolDown;
	}

}

