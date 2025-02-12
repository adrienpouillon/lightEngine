#include "Plant.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"


void Plant::OnInitialize()
{
	Alive::OnInitialize(5000);
	StateManager::Init(3, 3, 1, SHOOTINGUSE, this);
	SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green);
}

void Plant::OnCollision(Entity* other)
{
	if (GetScene<Garden>()->GetTypeConvert<Zombie*>(other))
	{
		Alive::LifeLessLess();
	}
	else if (Shot* shot = GetScene<Garden>()->GetTypeConvert<Shot*>(other))
	{
		if (shot->GetType() == TYPEZOMBIE)
		{
			Alive::LifeLessLess();
		}
	}
	SetIsCollide(true);
}

void Plant::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());
}

void Plant::ActionDead()
{
	StateManager::Destroy();
	Entity::Destroy();
}

void Plant::SetLife(int life)
{
	Alive::SetLife(life);
}

int Plant::GetType()
{
	return TYPEPLANT;
}
