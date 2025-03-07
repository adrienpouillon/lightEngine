#include "Plant.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"


void Plant::OnInitialize()
{
	Alive::OnInitialize(5000);
	StateManager::InitBase(this);
	SetTag(TYPEPLANT);
}

void Plant::OnCollision(Entity* other)
{
	
}

void Plant::OnUpdate()
{
	Alive::OnUpdate();
	StateManager::OnUpdate(GetDeltaTime());

	if(GetScene<Garden>()->GetIaPlant())
	{
		IaAction();
	}
}

void Plant::IaAction()
{

}

void Plant::ActionDead()
{
	Garden* garden = GetScene<Garden>();
	garden->IncreasePlantEated();
	garden->IncreaseZombieCoin(1000);
	Entity::Destroy();
}

void Plant::SetLife(int life)
{
	Alive::SetLife(life);
}
