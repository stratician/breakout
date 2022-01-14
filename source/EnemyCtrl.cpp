#include "EnemyCtrl.h"
#include "Common.h"


EnemyCtrl::EnemyCtrl()
{

	textureTyp* textureData1 = new textureTyp;
	textureData1->tex = loadTexture(gRenderer, "assets/images/bowser.png", textureData1->width, textureData1->height);
	if (textureData1->tex != NULL)
	{
		textures.push_back(textureData1);
	}


	textureTyp* textureData2 = new textureTyp;
	textureData2->tex = loadTexture(gRenderer, "assets/images/bowser.png", textureData2->width, textureData2->height);
	if (textureData2->tex != NULL)
	{
		textures.push_back(textureData2);
	}
}

EnemyCtrl::~EnemyCtrl()
{
	for (int i = enemies.size(); i >= 0; --i)
	{
		enemies.erase(enemies.begin());
	}
}


void EnemyCtrl::Create(const int type, double x, double y)
{
	Enemy* enemy = new Enemy();
	
	enemy->Init(textures[type > 0 ? 1 : 0], (type > 0) ? 1 : 0, x, y, 0.0f, 0.0f, 1 + gLevel + type * 20 );

	enemies.push_back(enemy);
	
}

bool EnemyCtrl::Process()
{

	

	if (enemies.empty())
		return false;

	int nextAction = -1;


	


	for (int i= enemies.size()-1;i >= 0; --i)
	{
		if (enemies[i])
		{

			if (enemies[i]->getHealth() && enemies[i]->getY() > SCREEN_HEIGHT)
			{
				// Died
				bAlive = false;
				return false;
			}

			if (!enemies[i]->getHealth() || enemies[i]->getY() > SCREEN_HEIGHT)
			{
				// Destroy Enemy
				enemies.erase(enemies.begin() + i);
				continue;
			}
			
			
			enemies[i]->Process(nextAction);

			if (nextAction != -1)
			{
				// Change of Action
				break;
			}
		}
	}

	if (nextAction != -1)
	{
		for (int i = enemies.size() - 1; i >= 0; --i)
		{
			if (enemies[i])
			{
				enemies[i]->SetAction((ACTION)nextAction);
				enemies[i]->ApplyThrust({ 0.0, 1.0f });
			}
		}

		if (gGameSpeed < 25)
		{
			gGameSpeed *= 1.2f;
		}
	}


	
	return true;
	
}


void EnemyCtrl::DestroyAll()
{
	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		if (enemies[i])
		{
			// Destroy Enemy
			enemies.erase(enemies.begin() + i);
		}
	}
}

void EnemyCtrl::Render()
{
	for (Enemy *enemy : enemies)
	{
		if (enemy)
		{
			enemy->Render();
		}
	}
}

void EnemyCtrl::ProcessDestroy()
{
	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		if (enemies[i])
		{
			if (!enemies[i]->getHealth() )
			{
				// Destroy Enemy
				enemies.erase(enemies.begin() + i);
				continue;
			}
		}
	}
}