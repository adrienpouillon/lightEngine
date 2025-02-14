#pragma once
#include "Entity.h"
#include "Alive.h"
#include "StateManager.h"

#define TAGSHOOT1 0
#define TAGSHOOT2 TAGSHOOT1 + 1
#define TAGSHOOT3 TAGSHOOT2 + 1
#define TAGSHOOT4 TAGSHOOT3 + 1
#define TAGSHOOT5 TAGSHOOT4 + 1
#define TAGSHOOT6 TAGSHOOT5 + 1
#define TAGSHOOT7 TAGSHOOT6 + 1
#define TAGSHOOT8 TAGSHOOT7 + 1

#define MYLINE 0.f
#define UPLINE -5.f
#define DOWNLINE 5.f

class Plant :public Entity, public Alive, public StateManager
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void IaAction();

	virtual void OnShoot(int tag);

	virtual void ActionDead();

	void SetLife(int life);

	virtual int GetType();

};

