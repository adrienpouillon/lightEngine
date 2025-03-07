#include "Sun.h"
#include "Garden.h"
#include "Zombie.h"

void Sun::OnInitialize()
{
	SetTag(TYPEPLANT);
	SetDestroyTime(5.f);
}

void Sun::OnCollision(Entity* other)
{
	
}

void Sun::OnUpdate()
{
	Garden* garden = GetScene<Garden>();
	sf::Vector2f posMouse = garden->GetMousePosition();
	if (IsInside(posMouse.x, posMouse.y))
	{
		ActionDead();
	}

	if (garden->GetIaPlantCreat())
	{
		float time = GetDestroyTime();
		SetDestroyTime(time - GetDeltaTime());
		if (time < 0)
		{
			ActionDead();
		}
	}
}

void Sun::ActionDead()
{
	Garden* garden = GetScene<Garden>();
	float coef = (float)GetRadius() / (float)SUNRADIUS;
	garden->IncreasePlantCoin((int)(7.125f * coef * coef) + 1);
	Destroy();
}

void Sun::SetDestroyTime(float destroyTime)
{
	mDestroyProgress = destroyTime;
}

float Sun::GetDestroyTime()
{
	return mDestroyProgress;
}
