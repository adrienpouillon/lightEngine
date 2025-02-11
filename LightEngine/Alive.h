#pragma once

class Alive
{
protected:
	int mLife;
public:

	void OnInitialize(int life);

	void LifeLessLess();

	void OnUpdate();

	void IsDead();

	virtual void ActionDead() = 0;

	void SetLife(int life);

	int GetLife();
};

