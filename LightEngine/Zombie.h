#pragma once
#include "Entity.h"

#include "Utils.h"
#include "Alive.h"
#include "StateManager.h"

class Zombie :public Entity, public Alive, public StateManager
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void Collide(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	void OutGarden();

	void SetLife(int life);

protected:

	virtual ~Zombie() {};
};

