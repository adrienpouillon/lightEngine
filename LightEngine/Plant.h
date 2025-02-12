#pragma once
#include "Entity.h"
#include "Alive.h"
#include "StateManager.h"

class Plant :public Entity, public Alive, public StateManager
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

