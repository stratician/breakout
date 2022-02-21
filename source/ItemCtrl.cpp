#include "Common.h"


ItemCtrl::ItemCtrl()
{

	textureTyp* textureData1 = new textureTyp;
	textureData1->tex = loadTexture(gRenderer, "assets/images/cube_blue.png", textureData1->width, textureData1->height);
	if (textureData1->tex != NULL)
	{
		textures.push_back(textureData1);
	}


	textureTyp* textureData2 = new textureTyp;
	textureData2->tex = loadTexture(gRenderer, "assets/images/cube_red.png", textureData2->width, textureData2->height);
	if (textureData2->tex != NULL)
	{
		textures.push_back(textureData2);
	}

	


}

ItemCtrl::~ItemCtrl()
{
	for (int i = 0; i < textures.size(); ++i)
	{
		assert(textures[i]);

		SDL_DestroyTexture(textures[i]->tex);
	}
}


void ItemCtrl::Create(const int type, double x, double y, double vx, double vy)
{
	Item* item = new Item();
	
	switch (type)
	{
		case 0: // Default Weapon
			item->Init(textures[0], (ITEM_TYPE) type, x, y, vx, vy);
			break;
		case 1: // Red Flame
			item->Init(textures[1], (ITEM_TYPE)type, x, y, vx, vy);
			break;
		default: // Default Weapon
			item->Init(textures[0], (ITEM_TYPE) type, x, y, vx, vy);
			break;

	}
	items.push_back(item);
	
}

void ItemCtrl::Process()
{


	for (int i=items.size()-1;i >= 0; --i)
	{
		if (items[i])
		{
			if ( items[i]->y > SCREEN_HEIGHT || items[i]->Destroyed() )
			{
				// Destroy Item
				items.erase(items.begin() + i);
				continue;
			}
			
			items[i]->Process();
		}
	}
}

void ItemCtrl::Render()
{
	for (Item *item : items)
	{
		if (item)
		{
			item->Render();
		}
	}
}

std::vector<Item*> ItemCtrl::getItems() const
{
	return items;
}