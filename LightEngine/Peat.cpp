#include "Peat.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"

void Peat::OnInitialize()
{
	Plant::OnInitialize();
	SetTag(TYPEPLANTPEAT);
}

void Peat::OnCollision(Entity* other)
{
	if (other->GetTag() <= TYPEZOMBIE)
	{
		Alive::LifeLessLess();
	}
	SetIsCollide(true);
}

void Peat::OnUpdate()
{
	Plant::OnUpdate();
}

void Peat::IaAction()
{
	if (GetCanShoot() || GetCanReload())
	{
		bool noPlantUp = EUtils::IsEmptyEntityInLineUp<Plant>(this);
		bool noPlantDown = EUtils::IsEmptyEntityInLineDown<Plant>(this);
		if (EUtils::IsAlongLine(this) == false) {/*il y a un enemie*/
			if (noPlantUp)
			{
				/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
				if (noPlantDown)
				{
					/*il y a un enemie sur notre ligne mais pas de plante au dessus et au dessous*/
					if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
					{
						/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
						{
							/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
							{
								/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION8); }
								else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
							}
							else
							{
								/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
								else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
							}
						}
						else
						{
							/*il y a un enemie proche sur notre ligne*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
							{
								/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
								else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
							}
							else
							{
								/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
								if (GetCanShoot()) 
								{/*on peut tirer*/Shoot(TAGACTION2); }
								else if (GetCanReload()) {/*si peut super charger*/Reload(); }
							}
						}
					}
					else if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie proche sur la ligne du dessus et dessous mais pas de plante au dessous et au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION4); }
								else {/*tirer dessous*/Shoot(TAGACTION6); }
							}
							else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
						else
						{
							/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION4); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
					else if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
					else
					{
						/*il y a un enemie pas proche sur notre ligne et celle du dessus et celle du dessous mais pas de plante au dessus ou au dessous*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}
				else
				{
					/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
					if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
					{
						/*si enemie proche sur notre ligne*/
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
						{
							/*si enemie proche sur notre ligne et celle du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION4); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
						else
						{
							/*si enemie proche sur notre ligne*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
					else
					{
						/*si enemie pas proche sur notre ligne*/
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
						{
							/*si enemie proche sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION4); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
						else
						{
							/*si enemie pas proche sur la ligne du dessus*/
							if (!EUtils::IsAlongLineUp(this))
							{
								/*si enemie sur la ligne du dessus*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION1); }
									else {/*tirer dessous*/Shoot(TAGACTION3); }
								}
								else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
							}
							else
							{
								/*si pas enemie sur la ligne du dessus*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION1); }
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
					if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
					{
						/*si enemie proche sur notre ligne*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*si enemie proche sur notre ligne et celle du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
						else
						{
							/*si enemie proche sur notre ligne*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
					else
					{
						/*si enemie pas proche sur notre ligne*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*si enemie proche sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
						else
						{
							/*si enemie pas proche sur la ligne du dessous*/
							if (!EUtils::IsAlongLineDown(this))
							{
								/*si enemie sur la ligne du dessous*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION1); }
									else {/*tirer dessous*/Shoot(TAGACTION5); }
								}
								else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
							}
							else
							{
								/*si pas enemie sur la ligne du dessous*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION1); }
								else if (GetCanReload()) {/*si peut super charger*/Reload(); }
							}
						}
					}
				}
				else
				{
					/*il y a un enemie sur notre ligne*/
					if (!EUtils::IsAreaEmpty(this, GetRadius() * 5)) {/*si enemie proche*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
					}
					else
					{
						//si pas d'enemie proche
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION1); }
						else if (GetCanReload()) {/*si peut recharger*/Reload(); }
					}
				}
			}
		}
		else
		{//il y a personne sur notre ligne
			bool enemieUp = !EUtils::IsAlongLineUp(this);
			bool enemieDown = !EUtils::IsAlongLineDown(this);
			if (enemieUp && enemieDown) {/*il y a un enemie sur la ligne du dessus et du dessous*/
				if (noPlantUp)
				{
					/*il y a un enemie sur la ligne du dessus et du dessous mais pas de plante au dessus*/
					if (noPlantDown)
					{
						/*il y a un enemie sur la ligne du dessous mais pas de plante*/
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
						{
							/*il y a un enemie sur la ligne du dessus proche*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
							{
								/*il y a un enemie sur la ligne du dessus proche + un enemie sur la ligne du dessous proche*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION4); }
									else {/*tirer dessous*/Shoot(TAGACTION6); }
								}
								else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
							}
							else
							{
								/*il y a un enemie sur la ligne du dessus proche*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION4); }
								else if (GetCanReload()) {/*on peut recharger*/Reload(); }
							}
						}
						else
						{
							/*il y a un enemie sur la ligne du dessus mais pas proche*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
							{
								/*il y a un enemie sur la ligne du dessous proche*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6); }
								else if (GetCanReload()) {/*on peut recharger*/Reload(); }
							}
							else
							{
								/*il y a un enemie sur la ligne du dessous mais pas proche*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION3); }
									else {/*tirer dessous*/Shoot(TAGACTION5); }
								}
								else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
							}
						}
					}
					else
					{
						/*il y a un enemie sur la ligne du dessous avec une plante donc tire dessus*/ ////////////////////////////////
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
						{
							/*il y a un enemie sur la ligne du dessus proche*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION4); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
						else
						{
							/*il y a un enemie sur la ligne du dessus mais pas de plante*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION3); }
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
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
						{
							/*il y a un enemie sur la ligne du dessous proche*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6);}
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
						else
						{
							/*il y a un enemie sur la ligne du dessous mais pas proche*/
							if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION5); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
					else
					{
						/*il y a un enemie sur la ligne du dessous avec une plante*/
						if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessus proche*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tuer un max enemie sur la ligne du dessus ou dessous*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION4); }
									else {/*tirer dessous*/Shoot(TAGACTION6); }
								}
								else if (GetCanReload()) {/*on peut recharger*/Reload(); }
							}
							else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION3); }
								else if (GetCanReload()) {/*on peut recharger*/Reload(); }
							}
						}
						else {/*il y a un enemie sur la ligne du dessus mais pas proche*/
							if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tirer sur la ligne du dessous*/
								if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION5); }
								else if (GetCanReload()) {/*on peut recharger*/Reload(); }
							}
							else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus ou dessous*/
								if (GetCanShoot()) {/*on peut tirer*/
									if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION3); }
									else {/*tirer dessous*/Shoot(TAGACTION5); }
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
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
					{
						/*il y a un enemie sur la ligne du dessus proche*/
						if (GetCanShoot()){/*on peut tirer*/Shoot(TAGACTION4);}
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
					else
					{
						/*il y a un enemie sur la ligne du dessus mais pas de plante*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION3); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
				else
				{
					/*il y a un enemie sur la ligne du dessus et une plante*/
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION3); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}
			else if (enemieDown) {/*il y a un enemie sur la ligne du dessous*/
				if (noPlantDown)
				{
					/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
					{
						/*il y a un enemie sur la ligne du dessous proche*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION6); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
					else
					{
						/*il y a un enemie sur la ligne du dessous mais pas de plante*/
						if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION5); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
				else
				{
					if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION5); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}
			else if (GetCanReload()) {/*on peut super charger*/SuperReload(); }
		}
	}
}

void Peat::OnShoot(int tag)
{
	Garden* garden = GetScene<Garden>();
	switch (tag)
	{
	case TAGACTION1:
		//tirer sur notre ligne
		garden->InstanceShot(this, MYLINE);
		break;
	case TAGACTION2:
		//super tirer sur notre ligne
		garden->InstanceShotRoc(this, MYLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGACTION3:
		//tirer sur la ligne du dessus
		garden->InstanceShot(this, UPLINE);
		break;
	case TAGACTION4:
		//super tirer sur la ligne du dessus
		garden->InstanceShotRoc(this, UPLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGACTION5:
		//tirer sur la ligne du dessous
		garden->InstanceShot(this, DOWNLINE);
		break;
	case TAGACTION6:
		//super tirer sur la ligne du dessous
		garden->InstanceShotRoc(this, DOWNLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGACTION7:
		//tirer sur la ligne du dessus et du dessous
		garden->InstanceShot(this, UPLINE);
		garden->InstanceShot(this, DOWNLINE);
		break;
	case TAGACTION8:
		//super tirer sur la ligne du dessus et du dessous
		garden->InstanceShotRoc(this, UPLINE);
		garden->InstanceShotRoc(this, DOWNLINE);
		AmmoLessLess();
		AmmoLessLess();
		break;
	}
}
