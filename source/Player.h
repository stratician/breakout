#pragma once

#include "Entity.h"




class Player: public Entity
{
protected:


	HealthBar *weaponEnergyBar; // We use the same health bar class for weapon energy;
	
public:

	Player();
	virtual ~Player();

	bool Init(OWNER_TYPE ownerType, int life);
	void ProcessInput();
	void Process();
	void Render();
	

};

