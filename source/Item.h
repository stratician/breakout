#pragma once


#include "Sprite.h"


struct textureTyp;

enum class ITEM_TYPE {
	DEFAULT,
	RED_FLAME,
	BLUE_FLAME,
};

class Item
{

public:
	double x, y;

private:

	SDL_Texture* tex;
	CSprite* spr;

	ITEM_TYPE type;
	int texWidth;
	int texHeight;

	
	double vx, vy;
	int life;

	double width;
	double height;

	double sx;
	double sy;

	int cyc32;

	bool bDestroy;

public:

	Item();
	virtual ~Item();
	bool Init(textureTyp* texureData, ITEM_TYPE type, double x, double y, double vx, double vy);
	void Process();
	void Render() const;
	void Destroy();
	bool Destroyed() const;
	ITEM_TYPE GetType() const;
	
};

