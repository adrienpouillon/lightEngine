#include "Zombie.h"
#include "Garden.h"
#include "Shot.h"

void Zombie::OnInitialize()
{
	Alive::OnInitialize(3);
	sf::Vector2f pos = GetPosition();
	Entity::GoToDirection(pos.x - 1, pos.y, 20.f);
	StateManager::Init(3, 3, 1, WALKINGUSE, this);
	SetAllColor(sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red, sf::Color::Red);
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
	SetIsCollide(true);
}

void Zombie::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());
}

void Zombie::ActionDead()
{
	StateManager::Destroy();
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
