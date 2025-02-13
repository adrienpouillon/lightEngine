#include "Plant.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"


void Plant::OnInitialize()
{
	Alive::OnInitialize(5000);
	StateManager::Init(3, 3.f, 1.f, 1.f, SHOOTINGUSE, this);
	SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green);
	mState = State::Full;
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

	IaAction();
}

void Plant::IaAction()
{
	if (GetScene<Garden>()->IsAlongLine(this) == false)
	{
		if (GetCanShoot())
		{
			Shoot(TAGSHOOT1);
		}
		else if (GetCanReload())
		{
			Reload();
		}
	}
	else
	{
		if (GetScene<Garden>()->IsAlongLineUp(this) == false)
		{
			if (GetCanShoot())
			{
				Shoot(TAGSHOOT3);
			}
			else if (GetCanReload())
			{
				Reload();
			}
		}
		else if (GetScene<Garden>()->IsAlongLineDown(this) == false)
		{
			if (GetCanShoot())
			{
				Shoot(TAGSHOOT5);
			}
			else if (GetCanReload())
			{
				Reload();
			}
		}
		else if (GetCanReload())
		{
			Reload();
		}
	}
}

void Plant::OnShoot(int tag)
{
	switch(tag)
	{
	case TAGSHOOT1:
		GetScene<Garden>()->InstanceShot(this, MYLINE);
		break;
	case TAGSHOOT2:
		GetScene<Garden>()->InstanceShotRoc(this, MYLINE);
		break;
	case TAGSHOOT3:
		GetScene<Garden>()->InstanceShot(this, UPLINE);
		break;
	case TAGSHOOT4:
		GetScene<Garden>()->InstanceShotRoc(this, UPLINE);
		break;
	case TAGSHOOT5:
		GetScene<Garden>()->InstanceShot(this, DOWNLINE);
		break;
	case TAGSHOOT6:
		GetScene<Garden>()->InstanceShotRoc(this, DOWNLINE);
		break;
	}
	
}

void Plant::ActionDead()
{
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
