#pragma once


#include "Enemy.h"
#include <memory>
#include <vector>
#include "Bullet.h"

struct textureTyp;
class Enemy;
class Bullet;

class EnemyCtrl
{
private:
	std::vector<textureTyp*> textures;

	std::vector<Enemy*> enemies;
		
public:

	EnemyCtrl();
	virtual ~EnemyCtrl();
	void Create(const int type, double x, double y);
	bool Process();
	void ProcessDestroy();
	void Render();
	void DestroyAll();
	

};

