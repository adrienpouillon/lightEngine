#pragma once
#include "Entity.h"
#include "Utils.h"
#include "Alive.h"

class Shot :public Entity, public Alive
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	void InsertInLine();

	virtual void ActionDead();

	void SetLife(int life);

	virtual void SetTag(int type);

	void SetDirectionShot(sf::Vector2f pos);

};

