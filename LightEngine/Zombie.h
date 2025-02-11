#pragma once
#include "Entity.h"
#include "Alive.h"

class Zombie :public Entity, public Alive
{
protected:


public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	void SetLife(int life);

	virtual int GetType();

};

