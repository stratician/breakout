#pragma once

#include "Entity.h"




class Player: public Entity
{
protected:

	
public:

	Player();
	virtual ~Player();

	bool Init(OWNER_TYPE ownerType, int life);
	void ProcessInput();
	void Process();
	void Render();
	

};

