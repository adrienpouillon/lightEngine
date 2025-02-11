#include "Plant.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"


void Plant::OnInitialize()
{
	Alive::OnInitialize(5000);
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
}

void Plant::OnUpdate()
{
	Alive::OnUpdate();
}

void Plant::ActionDead()
{

	Destroy();
}

void Plant::SetLife(int life)
{
	Alive::SetLife(life);
}

int Plant::GetType()
{
	return TYPEPLANT;
}
