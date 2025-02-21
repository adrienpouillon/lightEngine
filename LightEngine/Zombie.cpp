#include "Zombie.h"
#include "Garden.h"
#include "Shot.h"
#include "Plant.h"

void Zombie::OnInitialize()
{
	Alive::OnInitialize(3);
	float speed = 20.f;
	sf::Vector2f pos = GetPosition();
	Entity::GoToDirection((int)pos.x - 1, (int)pos.y, speed);
	StateManager::InitBase(this);
}

void Zombie::OnCollision(Entity* other)
{
	if (other != nullptr)
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
	else
	{
		Destroy();
		GetScene<Garden>()->IncreaseZombiePass();
	}
}

void Zombie::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());
	float zombieWidth = mShape.getRadius() * 2.f;
	Entity::OutWindow(zombieWidth, zombieWidth * 10.f);
}

void Zombie::ActionDead()
{
	GetScene<Garden>()->IncreaseZombieDestroy();
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
