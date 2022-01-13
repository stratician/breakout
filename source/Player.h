#pragma once


#include "Sprite.h"
#include "Bullet.h"
#include "HealthBar.h"

class HealthBar;

enum WEAPON_TYPE {
	WEAPON_DEFAULT,
	WEAPON_RED_FLAME,
	WEAPON_BLUE_FLAME,
	WEAPON_CONCAT,
};

class Bullet;

class Player
{
protected:

	SDL_Texture* tex;
	CSprite* spr;
	HealthBar* healthbar;

	int texWidth;
	int texHeight;

	double x, y;
	double vx, vy;
	int life;

	double width;
	double height;

	double sx;
	double sy;

	int weaponType;
	int coolDown;

	OWNER_TYPE ownerType;

	int radius;

public:

	Player();
	virtual ~Player();

	virtual bool Init(OWNER_TYPE ownerType);
	virtual void ProcessInput();
	virtual void Process();
	virtual void Render();
	virtual void SetWeapon(const int type);
	virtual void Fire(double vx, double vy, bool bCoolDown = true);
	virtual bool BulletHit(Bullet* bullet, double radius);
	virtual void ProcessHitByBullets(Bullet* bullet);
	virtual bool ApplyDamage(int damage);

	CSprite* getSpr() const;

	double getX() const;
	double getY() const;

	int getLife() const;
	void Respawn();

};

