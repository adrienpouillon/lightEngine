#pragma once
#include "Entity.h"
#include "Alive.h"

class Shot :public Entity, public Alive
{
protected:
	int mType;

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	void SetLife(int life);

	void SetType(int type);

	virtual int GetType();

};

