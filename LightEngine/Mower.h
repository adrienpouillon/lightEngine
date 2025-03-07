#pragma once
#include "Entity.h"

class Mower :public Entity
{
protected:
	bool mActivate;
	bool mFirst;
public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

};

