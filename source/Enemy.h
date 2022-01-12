#pragma once


#include "Player.h"
#include "Common.h"


enum ACTION {
	AI_LEFT,
	AI_RIGHT,
	AI_FIRE,
};

struct Vec;
struct textureTyp;
class Player;

class Enemy: public Player
{
private:
	int type;
	int action;
public:

	Enemy();
	virtual ~Enemy();

	bool Init(textureTyp* texureData, const int type, double x, double y, double vx, double vy, int life);
	void Process(int& nextDirection);
	void Render();
	void SetWeapon(const int type);
	void Fire(double vx, double vy);
	void SetAction(int action);
	void ApplyThrust(Vec dir);
	

	double getX() const;
	double getY() const;

};

