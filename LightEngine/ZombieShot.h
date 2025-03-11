#pragma once
#include "Zombie.h"
#include "defineShot.h"

class ZombieShot :public Zombie
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void Collide(Entity* other);

	virtual void OnUpdate();

	void IaAction();

	virtual void ActionDead();

	void OnShoot(int tag);

};

