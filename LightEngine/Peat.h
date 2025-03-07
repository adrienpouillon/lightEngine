#pragma once
#include "Plant.h"

class Peat :public Plant
{
protected:
	
public:
	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void IaAction();

	virtual void OnShoot(int tag);
};

