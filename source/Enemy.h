#pragma once


#include "Entity.h"
#include "Common.h"


enum class ACTION {
	AI_LEFT,
	AI_RIGHT,
	AI_FIRE,
};

struct Vec;
struct textureTyp;


class Enemy: public Entity
{
private:
	int type;
	ACTION action;
	
public:

	Enemy();
	virtual ~Enemy();

	bool Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int health);
	void Process(int& nextDirection);
	void Render();
	void SetWeapon(const int type);
	void Fire(double vx, double vy);
	void SetAction(ACTION action);
	void ApplyThrust(Vec dir);
	
};

