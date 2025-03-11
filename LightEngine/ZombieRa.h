#pragma once
#include "Zombie.h"
class ZombieRa :public Zombie
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	void Collide(Entity* other);

	virtual void OnUpdate();

	void AttactSun();

	virtual void ActionDead();

};

