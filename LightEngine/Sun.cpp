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
	if (other == nullptr)
	{
		Destroy();
	}
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

	if (mTarget.isSet)
	{
		float SunWidth = mShape.getRadius() * 2.f;
		sf::Vector2i size = GameManager::Get()->GetWindowSize();
		Entity::OutWindow(size.y*3, SunWidth);
	}
}

void Sun::ActionDead()
{
	ActionDeadPlant();
}

void Sun::ActionDeadPlant()
{
	Garden* garden = GetScene<Garden>();
	float coef = (float)GetRadius() / (float)SUNRADIUS;
	if(coef == 1)
	{
		garden->IncreasePlantCoin((int)(3.562f) + 1);
	}
	else
	{
		garden->IncreasePlantCoin((int)(3.562f * coef * coef * coef * coef) + 1);
	}
	Destroy();
}

void Sun::ActionDeadZombie()
{
	Garden* garden = GetScene<Garden>();
	float coef = (float)GetRadius() / (float)SUNRADIUS;
	garden->IncreaseZombieCoin((int)(100.f * coef * coef) + 1);
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

void Sun::SetFallSun()
{
	sf::Vector2f pos = GetPosition();
	sf::Vector2i size = GameManager::Get()->GetWindowSize();
	if (pos.y < 0.f)
	{
		int ran = Garden::GenerateRandomNumber(0, 20);
		GoToPosition(pos.x, pos.y + (float)(size.y * 2), 100.f + (float)ran, false);
	}
}
