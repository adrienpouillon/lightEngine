#include "Shot.h"
#include "Garden.h"
#include "Zombie.h"

void Shot::OnInitialize()
{
	Alive::OnInitialize(1);
	sf::Vector2f pos = GetPosition();
	Entity::GoToDirection(pos.x + 1, pos.y, 200.f);
	mType = TYPEPLANT;
}

void Shot::OnCollision(Entity* other)
{
	if(other != nullptr)
	{
		if (Zombie* zombie = GetScene<Garden>()->GetTypeConvert<Zombie*>(other))
		{
			if (zombie->GetType() != mType)
			{
				Alive::LifeLessLess();
			}
		}
		else if (Shot* shot = GetScene<Garden>()->GetTypeConvert<Shot*>(other))
		{
			if (shot->GetType() != mType)
			{
				Alive::LifeLessLess();
			}
		}
	}
	else
	{
		//sorti de l'ecran
		Destroy();
	}
}

void Shot::OnUpdate()
{
	Alive::OnUpdate();
	Entity::OutWindow(1000,0);
}

void Shot::ActionDead()
{

	Destroy();
}

void Shot::SetLife(int life)
{
	Alive::SetLife(life);
}

void Shot::SetType(int type)
{
	mType = type;
	if (mType == TYPEPLANT)
	{
		sf::Vector2f pos = GetPosition();
		Entity::GoToDirection(pos.x + 1, pos.y, 200.f);
	}
	else if (mType == TYPEZOMBIE)
	{
		sf::Vector2f pos = GetPosition();
		Entity::GoToDirection(pos.x - 1, pos.y, 200.f);
	}
}

int Shot::GetType()
{
	return mType;
}
