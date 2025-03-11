#pragma once
#include "Plant.h"
class SunFlower : public Plant
{
protected:
	
public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	virtual void IaAction();

	void IsAreaEmptyAction(int tagEmpty, int tagNoEmpty);

	void OnBoost(int tag);

	sf::Vector2f MoreLessWithRadius();

};

