#include "Shot.h"
#include "Garden.h"
#include "Zombie.h"

void Shot::OnInitialize()
{
	Alive::OnInitialize(1);
	SetType(TYPEPLANT);
	//sf::Vector2f pos = GetPosition();
	//Entity::GoToDirection(pos.x + 1, pos.y, 200.f);
	//mType = TYPEPLANT;
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
	InsertInLine();
}

void Shot::InsertInLine()
{
	sf::Vector2f pos = GetPosition();
	sf::Vector2f direction = GetDirection();
	if(direction != sf::Vector2f(pos.x - 1, pos.y) || direction != sf::Vector2f(pos.x + 1, pos.y))
	{
		float moreLess = 5.f;
		if (pos.y - moreLess < LINEONE && pos.y + moreLess > LINEONE)
		{
			SetPosition(GetPosition().x, LINEONE);
			SetDirectionShot(GetPosition());
		}
		if (pos.y - moreLess < LINETWO && pos.y + moreLess > LINETWO)
		{
			SetPosition(GetPosition().x, LINETWO);
			SetDirectionShot(GetPosition());
		}
		if (pos.y - moreLess < LINETHREE && pos.y + moreLess > LINETHREE)
		{
			SetPosition(GetPosition().x, LINETHREE);
			SetDirectionShot(GetPosition());
		}
	}
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
	SetDirectionShot(GetPosition());
}

void Shot::SetDirectionShot(sf::Vector2f pos)
{
	if (mType == TYPEPLANT)
	{
		Entity::GoToDirection(pos.x + 1, pos.y, 200.f);
	}
	else if (mType == TYPEZOMBIE)
	{
		Entity::GoToDirection(pos.x - 1, pos.y, 200.f);
	}
}

int Shot::GetType()
{
	return mType;
}
