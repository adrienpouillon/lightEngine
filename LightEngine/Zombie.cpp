#include "Zombie.h"
#include "Garden.h"
#include "Shot.h"

void Zombie::OnInitialize()
{
	Alive::OnInitialize(3);
	sf::Vector2f pos = GetPosition();
	Entity::GoToDirection(pos.x - 1, pos.y, 20.f);
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
}

void Zombie::OnUpdate()
{
	Alive::OnUpdate();
}

void Zombie::ActionDead()
{

	Destroy();
}

void Zombie::SetLife(int life)
{
	Alive::SetLife(life);
}

int Zombie::GetType()
{
	return TYPEZOMBIE;
}
