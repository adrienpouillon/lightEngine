#include "Zombie.h"
#include "Garden.h"
#include "Shot.h"
#include "Plant.h"

void Zombie::OnInitialize()
{
	Alive::OnInitialize(3);
	sf::Vector2f pos = GetPosition();
	Entity::GoToDirection(pos.x - 1, pos.y, 20.f);
	StateManager::Init(3, 0.f, 0.f, 0.f, WALKINGUSE, this);
	SetAllColor(sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red);
	mState = State::Walking;
}

void Zombie::OnCollision(Entity* other)
{
	if (Shot* shot = GetScene<Garden>()->GetTypeConvert<Shot*>(other))
	{
		if (shot->GetType() == TYPEPLANT)
		{
			Alive::LifeLessLess();
		}
	}
	if (Plant* plant = GetScene<Garden>()->GetTypeConvert<Plant*>(other))
	{
		SetIsCollide(true);
	}
	
}

void Zombie::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());
}

void Zombie::ActionDead()
{
	Entity::Destroy();
}

void Zombie::SetLife(int life)
{
	Alive::SetLife(life);
}

int Zombie::GetType()
{
	return TYPEZOMBIE;
}
