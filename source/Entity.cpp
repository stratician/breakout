#include "Entity.h"
#include "Common.h"


int weaponCoolDownLst[] = { 15, 3, 2, 30 };

Entity::Entity()
{

}

Entity::~Entity()
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

	if (healthbar)
	{
		delete healthbar;
	}
}


bool Entity::Init(OWNER_TYPE ownerType, int health)
{

	this->health = health;
	this->maxHealth = health;
	radius = 60.0f; // Default

	this->ownerType = ownerType;
	healthbar = new HealthBar(this, this->health, 60, 6);

	return true;
}

void Entity::SetWeapon(const WEAPON_TYPE type)
{
	this->weaponType = type;
	this->coolDown = weaponCoolDownLst[(int)type];
}


void Entity::Fire(double vx, double vy, bool bCoolDown)
{
	if (coolDown)
		return;

	// Fire Bullet
	switch (weaponType)
	{
	case WEAPON_TYPE::WEAPON_DEFAULT:
		bulletCtrl->Create((int)weaponType, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
		break;

	case WEAPON_TYPE::WEAPON_RED_FLAME:
		bulletCtrl->Create((int)weaponType, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
		break;
	}

	if (bCoolDown)
	{
		// Reset the cool down for our weapon
		coolDown = weaponCoolDownLst[(int)weaponType];
	}


}



void Entity::Render()
{
	spr->Render(gRenderer, x, y, sx, sy, 0.0, true);

	if (healthbar)
	{
		healthbar->Render();
	}
}



void Entity::Process()
{


	// Detections with Bullets
	std::vector<Bullet*> bullets = bulletCtrl->getBullets();
	for (Bullet* bullet : bullets)
	{
		ProcessHitByBullets(bullet);
	}

	if (coolDown)
	{
		coolDown--;
	}

}

double Entity::getX() const
{
	return this->x;
}

double Entity::getY() const
{
	return this->y;
}

double Entity::getWidth() const
{
	return this->width;
}

double Entity::getHeight() const
{
	return this->height;
}



int Entity::getHealth() const
{
	return health;
}

int Entity::getMaxHealth() const
{
	return maxHealth;
}


bool Entity::BulletHit(Bullet* bullet, double radius)
{
	// Only consider bullets that are not our our ownerType
	if (this->ownerType == bullet->getOwnerType())
	{
		return false;
	}


	// Simple radial collision
	Vec dist = { bullet->x - this->x, bullet->y - this->y };

	return dist.length2() < radius * radius;
	
}

bool Entity::ApplyDamage(int damage)
{
	if (health > 0)
	{
		health -= damage;
	}
	
	if(health < 0)
	{
		health = 0;
	}


	return health > 0;
}

void Entity::ProcessHitByBullets(Bullet* bullet)
{
	if (BulletHit(bullet, this->radius))
	{
		// Destroy Enemy
		if (!ApplyDamage(1))
		{
			health = 0;
		}

		// destroy bullet
		bullet->ApplyDamage(1000);
	}
	
}

void Entity::Respawn(double x, double y)
{
	this->health = this->maxHealth;


	this->x = x;
	this->y = y;

}

CSprite* Entity::getSpr() const
{
	return spr;
}