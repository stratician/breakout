#pragma once

#include "Player.h"

class Player;

class HealthBar
{
private:
	double width, height;
	int maxHealth;
	int health;
	Player* owner;

public:

	HealthBar(Player* owner, int maxHealth, double width, double height);
	virtual ~HealthBar();
	
	void Update(int health);
	void Process();
	void Render() const;
	
};

