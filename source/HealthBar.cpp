#include "HealthBar.h"
#include "Common.h"


HealthBar::HealthBar(Entity* owner, int maxHealth, double width, double height)
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

	double width = this->width * (owner->getWidth() / 100.0f);

	if (this->health > 0)
	{
		double height = owner->getHeight();

		SDL_Rect rect = { owner->getX() - width / 2, owner->getY() + owner->getHeight() * 0.4, width, this->height };
		SDL_SetRenderDrawColor(gRenderer, 20, 60, 33, 128);
		SDL_RenderFillRect(gRenderer, &rect);

		double percent = (double)owner->getHealth() / (double)owner->getMaxHealth();
		SDL_Rect rect2 = { owner->getX() - width / 2, owner->getY() + owner->getHeight() * 0.4 + 1, width * percent, this->height - 2 };
		SDL_SetRenderDrawColor(gRenderer, 0, 240, 40, 165);
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
