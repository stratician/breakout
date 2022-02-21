#include "Entity.h"
#include "Common.h"


int weaponCoolDownLst[] = { 15, 6, 5, 30 };

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
	weaponEnergy = 0;

	this->ownerType = ownerType;
	healthbar = new HealthBar(this, this->health, 60, 6);

	maxWeaponEnergy = 60 * 10;
	cyc16 = 0;

	return true;
}

void Entity::SetWeapon(const WEAPON_TYPE type)
{
	this->weaponType = type;
	this->coolDown = weaponCoolDownLst[(int)type];
}


void Entity::Fire(double vx, double vy, bool bPrimary, bool bCoolDown)
{
	if (coolDown)
		return;

	WEAPON_TYPE type = weaponType;
	if (bPrimary)
	{
		type = WEAPON_TYPE::WEAPON_DEFAULT;
	}

	// Fire Bullet
	switch (type)
	{
	case WEAPON_TYPE::WEAPON_DEFAULT:
		bulletCtrl->Create((int)type, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
		break;

	case WEAPON_TYPE::WEAPON_RED_FLAME:
		bulletCtrl->Create((int)type, this->x, this->y - this->height * 0.7f, vx, vy, ownerType);
		break;
	}

	if (bCoolDown)
	{
		// Reset the cool down for our weapon
		coolDown = weaponCoolDownLst[(int)type];
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


	// Detections with Items (for Players)
	if (this->ownerType == OWNER_TYPE::OWNER_PLAYER)
	{
		std::vector<Item*> items = itemCtrl->getItems();
		for (Item* item : items)
		{
			ProcessCollideWithItem(item);
		}
	}


	if (coolDown)
	{
		coolDown--;
	}

	cyc16++;
	if (cyc16 == 16)
	{
		cyc16 = 0;
		if (weaponType != WEAPON_TYPE::WEAPON_DEFAULT)
		{
			cyc16 = cyc16;
		}
	}

	if (weaponEnergy)
	{
		if (weaponType != WEAPON_TYPE::WEAPON_DEFAULT)
		{
			if (!cyc16 || (KEY_FIRE_ALT && weaponType != WEAPON_TYPE::WEAPON_DEFAULT))
			{
				weaponEnergy--;
			}
		}
	}
	else
	{
		weaponType = WEAPON_TYPE::WEAPON_DEFAULT;
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

			// If we're an AI, chance of spawning Item
			if (this->ownerType == OWNER_TYPE::OWNER_AI)
			{
				if (rand() % 3 == 0)
				{
					itemCtrl->Create(1, this->x, this->y, 0.0f, 1.0f);
				}
			}
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



void Entity::ProcessCollideWithItem(Item* item)
{

	// Simple radial collision
	Vec dist = { item->x - this->x, item->y - this->y };

	if (dist.length2() < radius * radius)
	{
		// Collect Item
		ITEM_TYPE type = item->GetType();

		switch (type)
		{
			case ITEM_TYPE::DEFAULT:
				this->weaponType = WEAPON_TYPE::WEAPON_DEFAULT;
				break;
			case ITEM_TYPE::RED_FLAME:
				this->weaponType = WEAPON_TYPE::WEAPON_RED_FLAME;
				AddWeaponEnergy(60 * 2);
				break;
			case ITEM_TYPE::BLUE_FLAME:
				this->weaponType = WEAPON_TYPE::WEAPON_BLUE_FLAME;
				AddWeaponEnergy(60 * 2);
				break;
			default:
				this->weaponType = WEAPON_TYPE::WEAPON_DEFAULT;
				AddWeaponEnergy(60 * 2);
				break;
		}

		item->Destroy();
	}

}

void Entity::AddWeaponEnergy(int energy)
{
	this->weaponEnergy += energy;
	if (this->weaponEnergy > this->maxWeaponEnergy)
	{
		this->weaponEnergy = this->maxWeaponEnergy;
	}
}