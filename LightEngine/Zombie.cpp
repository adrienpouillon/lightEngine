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
	SetTag(TYPEZOMBIE);
}

void Zombie::OnCollision(Entity* other)
{
	if (other != nullptr)
	{
		Collide(other);
	}
	else
	{
		Destroy();
		Garden* garden = GetScene<Garden>();
		garden->IncreaseZombiePass();
		garden->IncreaseZombieCoin(250);
		garden->IncreasePlantCoin(-1);
	}
}

void Zombie::Collide(Entity* other)
{
	if (other->GetTag() >= TYPEPLANT)
	{
		if (Plant* plant = Garden::GetTypeConvert<Plant*>(other))
		{
			//activer le mode eating
			SetIsCollide(true);
		}
		else
		{
			Alive::LifeLessLess();
		}
	}
}

void Zombie::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());
	float zombieWidth = mShape.getRadius() * 2.f;
	Entity::OutWindow(sf::Vector2f(zombieWidth, 0.f), sf::Vector2f(COLLUMZOMBIE * 2, 0.f));
	OutGarden();
}

void Zombie::ActionDead()
{
	Garden* garden = GetScene<Garden>();
	garden->IncreaseZombieDestroy();
	garden->IncreasePlantCoin(1);
	Entity::Destroy();
}

void Zombie::OutGarden()
{
	sf::Vector2f pos = GetPosition();
	if (pos.x > COLLUMZOMBIE * 2)
	{
		SetPosition(COLLUMZOMBIE, pos.y);
	}
}

void Zombie::SetLife(int life)
{
	Alive::SetLife(life);
}
