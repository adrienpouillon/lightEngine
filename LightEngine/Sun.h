#pragma once
#include "Entity.h"

class Sun :public Entity
{
protected:
	float mDestroyProgress;
public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();
	virtual void ActionDeadPlant();
	virtual void ActionDeadZombie();

	void SetDestroyTime(float destroyTime);

	float GetDestroyTime();

	void SetFallSun();
	
};

