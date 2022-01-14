#pragma once

#include "Entity.h"

class Entity;

class HealthBar
{
private:
	double width, height;
	int maxHealth;
	int health;
	Entity* owner;

public:

	HealthBar(Entity* owner, int maxHealth, double width, double height);
	virtual ~HealthBar();
	
	void Update(int health);
	void Process();
	void Render() const;
	
};

