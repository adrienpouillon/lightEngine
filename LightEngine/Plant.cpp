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
	Garden* garden = GetScene<Garden>();
	if (garden->IsAlongLine(this) == false)
	{
		//il y a un enemie
		if (!garden->IsAreaEmpty(this, GetRadius() * 5))
		{
			//si enemie proche
			if (GetCanShoot())
			{
				//on peut tirer
				Shoot(TAGSHOOT2);
			}
			else if (GetCanReload())
			{
				//si peut super charger
				SuperReload();
			}
		}
		else
		{
			//si pas d'enemie proche
			if (GetCanShoot())
			{
				//on peut tirer
				Shoot(TAGSHOOT1);
			}
			else if (GetCanReload())
			{
				//si peut recharger
				Reload();
			}
		}
	}
	else
	{
		//il y a personne sur la ligne
		bool enemieUp = !garden->IsAlongLineUp(this);
		bool enemieDown = !garden->IsAlongLineDown(this);
		if (enemieUp && enemieDown)
		{
			//il y a un enemie sur la ligne du dessus et du dessous 
			//if (garden->IsEmptyPlantInLineUp(this)) { //il y a un enemie sur la ligne du dessus et du dessous et pas de plante } 
			if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
			{
				//il y a un enemie sur la ligne du dessus proche
				if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
				{
					//il y a un enemie sur la ligne du dessous proche
					//donc tuer un max enemie sur la ligne du dessus ou dessous
					if (GetCanShoot())
					{
						//on peut tirer
						int ran = GetScene()->GenerateRandomNumber(0, 1);
						if (ran == 0)
						{
							//tirer dessus
							Shoot(TAGSHOOT4);
						}
						else
						{
							//tirer dessous
							Shoot(TAGSHOOT6);
						}
						
					}
					else if (GetCanReload())
					{
						//on peut recharger
						Reload();
					}
				}
				else
				{
					//il y a un enemie sur la ligne du dessous mais pas proche
					//donc tirer sur la ligne du dessus
					if (GetCanShoot())
					{
						//on peut tirer
						Shoot(TAGSHOOT3);
					}
					else if (GetCanReload())
					{
						//on peut recharger
						Reload();
					}
				}
			}
			else
			{
				//il y a un enemie sur la ligne du dessus mais pas proche
				if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
				{
					//il y a un enemie sur la ligne du dessous proche
					//donc tirer sur la ligne du dessous
					if (GetCanShoot())
					{
						//on peut tirer
						Shoot(TAGSHOOT5);
					}
					else if (GetCanReload())
					{
						//on peut recharger
						Reload();
					}
				}
				else
				{
					//il y a un enemie sur la ligne du dessous mais pas proche
					//donc tirer sur la ligne du dessus ou dessous
					if (GetCanShoot())
					{
						//on peut tirer
						int ran = GetScene()->GenerateRandomNumber(0, 1);
						if (ran == 0)
						{
							//tirer dessus
							Shoot(TAGSHOOT3);
						}
						else
						{
							//tirer dessous
							Shoot(TAGSHOOT5);
						}
					}
					else if (GetCanReload())
					{
						//on peut recharger
						Reload();
					}
				}
			}
		}
		else if (enemieUp)
		{
			//il y a un enemie sur la ligne du dessus
			if (GetCanShoot())
			{
				//on peut tirer
				Shoot(TAGSHOOT3);
			}
			else if (GetCanReload())
			{
				//on peut recharger
				Reload();
			}
		}
		else if (enemieDown)
		{
			//il y a un enemie sur la ligne du dessous
			if (GetCanShoot())
			{
				//on peut tirer
				Shoot(TAGSHOOT5);
			}
			else if (GetCanReload())
			{
				//on peut recharger
				Reload();
			}
		}
		else if (GetCanReload())
		{
			//on peut super charger
			SuperReload();
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
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGSHOOT3:
		GetScene<Garden>()->InstanceShot(this, UPLINE);
		break;
	case TAGSHOOT4:
		GetScene<Garden>()->InstanceShotRoc(this, UPLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGSHOOT5:
		GetScene<Garden>()->InstanceShot(this, DOWNLINE);
		break;
	case TAGSHOOT6:
		GetScene<Garden>()->InstanceShotRoc(this, DOWNLINE);
		AmmoLessLess();
		AmmoLessLess();
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
