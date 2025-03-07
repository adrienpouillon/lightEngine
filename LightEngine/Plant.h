#pragma once
#include "Entity.h"
#include "Utils.h"
#include "Alive.h"
#include "StateManager.h"

#define MYLINE 0.f
#define UPLINE -5.f
#define DOWNLINE 5.f

#define TAGACTION1 0
#define TAGACTION2 TAGACTION1 + 1
#define TAGACTION3 TAGACTION2 + 1
#define TAGACTION4 TAGACTION3 + 1
#define TAGACTION5 TAGACTION4 + 1
#define TAGACTION6 TAGACTION5 + 1
#define TAGACTION7 TAGACTION6 + 1
#define TAGACTION8 TAGACTION7 + 1

class Plant :public Entity, public Alive, public StateManager
{
protected:
	
public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void IaAction();

	virtual void ActionDead();

	void SetLife(int life);

};

