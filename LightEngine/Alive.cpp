#include "Alive.h"

void Alive::OnInitialize(int life)
{
	SetLife(life);
}

void Alive::LifeLessLess()
{
	SetLife(mLife - 1);
}

void Alive::OnUpdate()
{
	IsDead();
}

void Alive::IsDead()
{
	if (mLife < 0)
	{
		ActionDead();
	}
}

void Alive::SetLife(int life)
{
	mLife = life;
}

int Alive::GetLife()
{
	return mLife;
}
