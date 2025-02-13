#pragma once
#include "Entity.h"
#include "Alive.h"
#include "StateManager.h"

class Zombie :public Entity, public Alive, public StateManager
{
protected:
	virtual ~Zombie() {};

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	void SetLife(int life);

	virtual int GetType();

};

