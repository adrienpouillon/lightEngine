#include "ZombieRa.h"
#include "Garden.h"
#include "Shot.h"
#include "Plant.h"
#include "Sun.h"

void ZombieRa::OnInitialize()
{
	Zombie::OnInitialize();
	SetTag(TYPEZOMBIERA);
}

void ZombieRa::OnCollision(Entity* other)
{
	Zombie::OnCollision(other);
}

void ZombieRa::Collide(Entity* other)
{
	if (other->GetTag() == TYPESUN)
	{
		if (Sun* sun = Garden::GetTypeConvert<Sun*>(other))
		{
			sun->ActionDeadZombie();
		}
	}
	else
	{
		Zombie::Collide(other);
	}
}

void ZombieRa::OnUpdate()
{
	Zombie::OnUpdate();
	AttactSun();
}

void ZombieRa::AttactSun()
{
	Garden* garden = GetScene<Garden>();
	std::vector<Sun*> allSun = garden->GetAllEntity<Sun>();
	int lenght = allSun.size() - 1;
	if (lenght < 0)
		return;

	int ran = Garden::GenerateRandomNumber(0, lenght);
	if(allSun[ran]->GetTargetIsSet() == false)
	{
		sf::Vector2f pos = GetPosition();
		allSun[ran]->GoToPosition(pos.x, pos.y, 100.f);
		allSun[ran]->GetShape()->setFillColor(sf::Color::Blue);
	}
}

void ZombieRa::ActionDead()
{
	Zombie::ActionDead();
	Garden* garden = GetScene<Garden>();
	garden->IncreasePlantCoin(9);
}