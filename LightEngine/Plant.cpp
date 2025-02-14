#include "Plant.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"


void Plant::OnInitialize()
{
	Alive::OnInitialize(5000);
	StateManager::Init(3, 0.f, 3.f, 1.f, 1.f, SHOOTINGUSE, this);
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
	bool noPlantUp = garden->IsEmptyPlantInLineUp(this);
	bool noPlantDown = garden->IsEmptyPlantInLineDown(this);
	if (garden->IsAlongLine(this) == false){/*il y a un enemie*/
		if (noPlantUp)
		{
			/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
			if (noPlantDown)
			{
				/*il y a un enemie sur notre ligne mais pas de plante au dessus et au dessous*/
				if (!garden->IsAreaEmpty(this, GetRadius() * 5))
				{
					/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT8); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
						else
						{
							/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
					}
					else
					{
						/*il y a un enemie proche sur notre ligne*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
						else
						{
							/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
				else if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
				{
					/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
					if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*il y a un enemie proche sur la ligne du dessus et dessous mais pas de plante au dessous et au dessous*/
						if (GetCanShoot()) {/*on peut tirer*/
							if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT4); }
							else {/*tirer dessous*/Shoot(TAGSHOOT6); }
						}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
					}
					else
					{
						/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}
				else if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
				{
					/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT6); }
					else if (GetCanReload()) {/*si peut super charger*/Reload(); }
				}
				else
				{
					/*il y a un enemie pas proche sur notre ligne et celle du dessus et celle du dessous mais pas de plante au dessus ou au dessous*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
					else if (GetCanReload()) {/*si peut super charger*/Reload(); }
				}
			}
			else
			{
				/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
				if (!garden->IsAreaEmpty(this, GetRadius() * 5))
				{
					/*si enemie proche sur notre ligne*/
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*si enemie proche sur notre ligne et celle du dessus*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
					else
					{
						/*si enemie proche sur notre ligne*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}
				else
				{
					/*si enemie pas proche sur notre ligne*/
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*si enemie proche sur la ligne du dessus*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
						else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
					}
					else
					{
						/*si enemie pas proche sur la ligne du dessus*/
						if(!garden->IsAlongLineUp(this))
						{
							/*si enemie sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT1); }
								else {/*tirer dessous*/Shoot(TAGSHOOT3); }
							}
							else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
						else
						{
							/*si pas enemie sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT1); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
			}
		}
		else
		{
			/*il y a un enemie sur notre ligne*/
			if (noPlantDown)
			{
				/*il y a un enemie sur notre ligne mais pas de plante au dessous*/
				if (!garden->IsAreaEmpty(this, GetRadius() * 5)) 
				{
					/*si enemie proche sur notre ligne*/
					if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*si enemie proche sur notre ligne et celle du dessous*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT6); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
					else
					{
						/*si enemie proche sur notre ligne*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}
				else
				{
					/*si enemie pas proche sur notre ligne*/
					if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*si enemie proche sur la ligne du dessous*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT6); }
						else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
					}
					else
					{
						/*si enemie pas proche sur la ligne du dessous*/
						if (!garden->IsAlongLineUp(this))
						{
							/*si enemie sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT1); }
								else {/*tirer dessous*/Shoot(TAGSHOOT5); }
							}
							else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
						else
						{
							/*si pas enemie sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT1); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
			}
			else
			{
				/*il y a un enemie sur notre ligne*/
				if (!garden->IsAreaEmpty(this, GetRadius() * 5)) {/*si enemie proche*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT2); }
					else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
				}
				else 
				{
					//si pas d'enemie proche
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT1); }
					else if (GetCanReload()) {/*si peut recharger*/Reload(); }
				}
			}
		}
	}
	else
	{//il y a personne sur notre ligne
		bool enemieUp = !garden->IsAlongLineUp(this);
		bool enemieDown = !garden->IsAlongLineDown(this);
		if (enemieUp && enemieDown) {/*il y a un enemie sur la ligne du dessus et du dessous*/
			if (noPlantUp)
			{
				/*il y a un enemie sur la ligne du dessus et du dessous mais pas de plante au dessus*/
				if (noPlantDown)
				{
					/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*il y a un enemie sur la ligne du dessus proche*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie sur la ligne du dessus proche + un enemie sur la ligne du dessous proche*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT4); }
								else {/*tirer dessous*/Shoot(TAGSHOOT6); }
							}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
						else
						{
							/*il y a un enemie sur la ligne du dessus proche*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
					else
					{
						/*il y a un enemie sur la ligne du dessus mais pas proche*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie sur la ligne du dessous proche*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT6); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
						else
						{
							/*il y a un enemie sur la ligne du dessous mais pas proche*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT3); }
								else {/*tirer dessous*/Shoot(TAGSHOOT5); }
							}
							else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
					}
				}
				else
				{
					/*il y a un enemie sur la ligne du dessous avec une plante donc tire dessus*/ ////////////////////////////////
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*il y a un enemie sur la ligne du dessus proche*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
					else
					{
						/*il y a un enemie sur la ligne du dessus mais pas de plante*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT3); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
			}
			else
			{
				/*il y a un enemie sur la ligne du dessus avec une plante*/
				if (noPlantDown)
				{
					/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*il y a un enemie sur la ligne du dessous proche*/
						if (GetCanShoot()) {/*on peut tirer*/
							Shoot(TAGSHOOT6); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
					else
					{
						/*il y a un enemie sur la ligne du dessous mais pas proche*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT5); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
				else
				{
					/*il y a un enemie sur la ligne du dessous avec une plante*/
					if (!garden->IsAreaEmptyUp(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessus proche*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tuer un max enemie sur la ligne du dessus ou dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT4); }
								else {/*tirer dessous*/Shoot(TAGSHOOT6); }
							}
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
						else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT3); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
					else {/*il y a un enemie sur la ligne du dessus mais pas proche*/
						if (!garden->IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tirer sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT5); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
						else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus ou dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGSHOOT3); }
								else {/*tirer dessous*/Shoot(TAGSHOOT5); }
							}
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
				}
			}
		}
		else if (enemieUp)
		{/*il y a un enemie sur la ligne du dessus*/
			if (noPlantUp)
			{
				/*il y a un enemie sur la ligne du dessus mais pas de plante*/
				if (!garden->IsAreaEmptyUp(this, GetRadius() * 5))
				{
					/*il y a un enemie sur la ligne du dessus proche*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT4); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
				else
				{
					/*il y a un enemie sur la ligne du dessus mais pas de plante*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT3); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}
			else
			{
				/*il y a un enemie sur la ligne du dessus et une plante*/
				if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT3); }
				else if (GetCanReload()) {/*on peut recharger*/Reload(); }
			}
		}else if (enemieDown){/*il y a un enemie sur la ligne du dessous*/
			if (noPlantDown)
			{ 
				/*il y a un enemie sur la ligne du dessous mais pas de plante*/ 
				if (!garden->IsAreaEmptyDown(this, GetRadius() * 5))
				{
					/*il y a un enemie sur la ligne du dessous proche*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT6); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
				else
				{
					/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT5); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}
			else
			{
				if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGSHOOT5); }
				else if (GetCanReload()) {/*on peut recharger*/Reload(); }
			}
		}else if (GetCanReload()){/*on peut super charger*/SuperReload();}
	}
}

void Plant::OnShoot(int tag)
{
	switch(tag)
	{
	case TAGSHOOT1:
		//tirer sur notre ligne
		GetScene<Garden>()->InstanceShot(this, MYLINE);
		break;
	case TAGSHOOT2:
		//super tirer sur notre ligne
		GetScene<Garden>()->InstanceShotRoc(this, MYLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGSHOOT3:
		//tirer sur la ligne du dessus
		GetScene<Garden>()->InstanceShot(this, UPLINE);
		break;
	case TAGSHOOT4:
		//super tirer sur la ligne du dessus
		GetScene<Garden>()->InstanceShotRoc(this, UPLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGSHOOT5:
		//tirer sur la ligne du dessous
		GetScene<Garden>()->InstanceShot(this, DOWNLINE);
		break;
	case TAGSHOOT6:
		//super tirer sur la ligne du dessous
		GetScene<Garden>()->InstanceShotRoc(this, DOWNLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGSHOOT7:
		//tirer sur la ligne du dessus et du dessous
		GetScene<Garden>()->InstanceShot(this, UPLINE);
		GetScene<Garden>()->InstanceShot(this, DOWNLINE);
		break;
	case TAGSHOOT8:
		//super tirer sur la ligne du dessus et du dessous
		GetScene<Garden>()->InstanceShotRoc(this, UPLINE);
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
