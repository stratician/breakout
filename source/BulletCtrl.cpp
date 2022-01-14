#include "Common.h"


int bulletLife[] = { 120, 40, 30, 120 };

BulletCtrl::BulletCtrl()
{

	textureTyp* textureData1 = new textureTyp;
	textureData1->tex = loadTexture(gRenderer, "assets/images/bullet_default.png", textureData1->width, textureData1->height);
	if (textureData1->tex != NULL)
	{
		textures.push_back(textureData1);
	}

	textureTyp* textureData2 = new textureTyp;
	textureData2->tex = loadTexture(gRenderer, "assets/images/redflameset8.png", textureData2->width, textureData2->height);
	if (textureData2->tex != NULL)
	{
		textures.push_back(textureData2);
	}

}

BulletCtrl::~BulletCtrl()
{
	for (int i = 0; i < textures.size(); ++i)
	{
		assert(textures[i]);

		SDL_DestroyTexture(textures[i]->tex);
	}
}


void BulletCtrl::Create(const int type, double x, double y, double vx, double vy, OWNER_TYPE ownerType)
{
	Bullet* bullet = new Bullet;
	
	bullet->Init(textures[type], (BULLET_TYPE)type, x, y, vx, vy, bulletLife[type], ownerType);

	bullets.push_back(bullet);
	
}

void BulletCtrl::Process()
{
	for (int i=bullets.size()-1;i >= 0; --i)
	{
		if (bullets[i])
		{
			if (!bullets[i]->getLife())
			{
				// Destroy Bullet
				bullets.erase(bullets.begin() + i);
				continue;
			}
			
			bullets[i]->Process();
		}
	}
}

void BulletCtrl::Render()
{
	for (Bullet *bullet : bullets)
	{
		if (bullet)
		{
			bullet->Render();
		}
	}
}

std::vector<Bullet*> BulletCtrl::getBullets() const
{
	return bullets;
}