#include "Mower.h"
#include "Garden.h"

void Mower::OnInitialize()
{
	mActivate = false;
	mFirst = true;
	SetTag(TYPEPLANTMOWER);
}

void Mower::OnCollision(Entity* other)
{
	if (other != nullptr)
	{
		if (other->GetTag() <= TYPEZOMBIE)
		{
			mActivate = true;
		}
	}
	else
	{
		//sorti de l'ecran
		Destroy();
	}
}

void Mower::OnUpdate()
{
	if (mActivate)
	{
		if (mFirst)
		{
			sf::Vector2f pos = GetPosition();
			GoToDirection(pos.x + 1, pos.y, 10.f);
			mFirst = false;
		}
	}
	float ShotWidth = mShape.getRadius() * 2.f;
	Entity::OutWindow(ShotWidth * 10.f, COLLUMZOMBIE * 2);
}

void Mower::ActionDead()
{
	Entity::Destroy();
}