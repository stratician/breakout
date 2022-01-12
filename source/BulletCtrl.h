#pragma once


#include "Sprite.h"
#include <memory>
#include <vector>
#include "Bullet.h"
#include "EnemyCtrl.h"

struct textureTyp;
class Bullet;

class BulletCtrl
{
private:

	std::vector<textureTyp*> textures;

	std::vector<Bullet*> bullets;

public:

	BulletCtrl();
	virtual ~BulletCtrl();
	void Create(const int type, double x, double y, double vx, double vy, OWNER_TYPE ownerType);
	void Process();
	void Render();
	std::vector<Bullet*> getBullets() const;

	
};

