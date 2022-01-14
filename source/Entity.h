#pragma once


#include "Sprite.h"
#include "HealthBar.h"
#include "Bullet.h"

class HealthBar;
class Bullet;

enum class WEAPON_TYPE {
	WEAPON_DEFAULT,
	WEAPON_RED_FLAME,
	WEAPON_BLUE_FLAME,
	WEAPON_CONCAT,
};


class Entity
{
protected:

	SDL_Texture* tex = nullptr;
	CSprite* spr = nullptr;
	HealthBar* healthbar;

	int texWidth;
	int texHeight;

	double x, y;
	double vx, vy;

	double width;
	double height;

	double sx;
	double sy;

	int coolDown;

	WEAPON_TYPE weaponType;
	OWNER_TYPE ownerType;


	int health;
	int maxHealth;
	double radius;

public:

	Entity();
	virtual ~Entity();

	virtual bool Init(OWNER_TYPE ownerType, int life);
	virtual void Process();
	virtual void Render();
	virtual bool BulletHit(Bullet* bullet, double radius);
	virtual void ProcessHitByBullets(Bullet* bullet);
	virtual bool ApplyDamage(int damage);
	virtual void Respawn(double x, double y);
	void SetWeapon(const WEAPON_TYPE type);
	virtual void Fire(double vx, double vy, bool bCoolDown = true);

	CSprite* getSpr() const;

	double getX() const;
	double getY() const;
	double getHeight() const;
	double getWidth() const;
	

	int getHealth() const;
	int getMaxHealth() const;


};

