#pragma once


#include "Sprite.h"
#include <memory>
#include <vector>
#include "Item.h"

struct textureTyp;
class Item;

class ItemCtrl
{
private:

	std::vector<textureTyp*> textures;

	std::vector<Item*> items;

public:

	ItemCtrl();
	virtual ~ItemCtrl();
	void Create(const int type, double x, double y, double vx, double vy);
	void Process();
	void Render();
	std::vector<Item*> getItems() const;

	
};

