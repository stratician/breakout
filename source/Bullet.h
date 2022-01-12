#pragma once


#include "Sprite.h"


struct textureTyp;

enum BULLET_TYPE {
	DEFAULT,
	RED_FLAME,
	BLUE_FLAME,
};

enum OWNER_TYPE {
	OWNER_PLAYER,
	OWNER_AI,
};

class Bullet
{

public:
	double x, y;

private:

	SDL_Texture* tex;
	CSprite* spr;

	int type;
	int texWidth;
	int texHeight;

	
	double vx, vy;
	int life;

	double width;
	double height;

	double sx;
	double sy;

	int cyc32;

	OWNER_TYPE ownerType;

public:

	Bullet();
	virtual ~Bullet();
	
	bool Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int life, OWNER_TYPE ownerType);
	void Process();
	void Render() const;
	int getLife() const;
	OWNER_TYPE getOwnerType() const;

	virtual bool ApplyDamage(int damage);

	

};

