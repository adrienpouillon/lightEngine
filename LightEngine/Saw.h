#pragma once
#include "Entity.h"
#include "Alive.h"

class Saw :public Entity, public Alive
{
protected:

public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void IaAction();

	void ActionDead();

	void SetLife(int life);

	void GoToPosition(int x, int line);

	void GoToPosition(sf::Vector2f xLine);

};

