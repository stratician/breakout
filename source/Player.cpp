#include "Player.h"
#include "Common.h"
#include "Bullet.h"


int weaponCoolDownLst[] = { 15, 3, 2, 30 };

Player::Player()
{

}

Player::~Player()
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


bool Player::Init(OWNER_TYPE ownerType)
{

	radius = 60.0f; // Default

	this->ownerType = ownerType;

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

	this->x = SCREEN_WIDTH / 2;
	this->y = SCREEN_HEIGHT - this->height / 2;

	this->vx = 0.1f;


	Respawn();
	SetWeapon(0);

	return true;
}


void Player::SetWeapon(const int type)
{
	this->weaponType = type;
	this->coolDown = weaponCoolDownLst[type];
}


void Player::Render()
{
	spr->Render(gRenderer, x, y, 0.3, 0.3f, 0.0, true);
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
		weaponType = 0;
		Fire(0.0f, -10.0f);
	}

	if (KEY_FIRE_ALT)
	{
		weaponType = 1;
		Fire(0.0f, -10.0f);
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
	

	if (coolDown)
	{
		--coolDown;
	}

	// Detections with Bullets
	std::vector<Bullet*> bullets = bulletCtrl->getBullets();
	for (Bullet* bullet : bullets)
	{
		ProcessHitByBullets(bullet);
	}


}

double Player::getX() const
{
	return this->x;
}

double Player::getY() const
{
	return this->y;
}

void Player::Fire(double vx, double vy, bool bCoolDown)
{
	if (coolDown)
		return;

	// Fire Bullet
	switch (weaponType)
	{
		case WEAPON_TYPE::WEAPON_DEFAULT:
			bulletCtrl->Create(weaponType, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
			break;

		case WEAPON_TYPE::WEAPON_RED_FLAME:
			bulletCtrl->Create(weaponType, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
			break;
	}
	
	if (bCoolDown)
	{
		// Reset the cool down for our weapon
		coolDown = weaponCoolDownLst[weaponType];
	}


}


int Player::getLife() const
{
	return life;
}


bool Player::BulletHit(Bullet* bullet, double radius)
{
	// Only consider bullets that are not our our ownerType
	if (this->ownerType == bullet->getOwnerType())
	{
		return false;
	}


	// Simple radial collision
	Vec dist = { bullet->x - this->x, bullet->y - this->y };
	return dist.length2() < radius* radius;
}

bool Player::ApplyDamage(int damage)
{
	if (life > 0)
	{
		life -= damage;
	}
	
	if(life < 0)
	{
		life = 0;
	}


	return life > 0;
}

void Player::ProcessHitByBullets(Bullet* bullet)
{
	if (BulletHit(bullet, this->radius))
	{
		// Destroy Enemy
		if (!ApplyDamage(1))
		{
			life = 0;
		}

		// destroy bullet
		bullet->ApplyDamage(1000);
	}
	
}

void Player::Respawn()
{
	life = 9; // 3 hits
}

CSprite* Player::getSpr() const
{
	return spr;
}