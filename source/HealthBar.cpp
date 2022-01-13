#include "HealthBar.h"
#include "Common.h"


HealthBar::HealthBar(Player* owner, int maxHealth, double width, double height)
{
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;

	this->owner = owner;
	this->width = width;
	this->height = height;
}

HealthBar::~HealthBar()
{
	
}



void HealthBar::Render() const
{
	assert(owner);

	if (this->health > 0)
	{

		SDL_Rect rect = { owner->getX() - this->width / 2, owner->getY(), this->width, this->height };
		SDL_SetRenderDrawColor(gRenderer, 33, 33, 33, 55);
		SDL_RenderFillRect(gRenderer, &rect);

		double percent = (double)this->health / (double)this->maxHealth;
		SDL_Rect rect2 = { owner->getX() - this->width / 2, owner->getY(), this->width * percent, this->height };
		SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
		SDL_RenderFillRect(gRenderer, &rect2);
	}
}


void HealthBar::Process()
{

	

}


void HealthBar::Update(int health)
{
	this->health = health;

}
