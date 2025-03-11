#include "ZombieShot.h"
#include "Plant.h"

void ZombieShot::OnInitialize()
{
	Zombie::OnInitialize();
	SetTag(TYPEZOMBIESHOT);
}

void ZombieShot::OnCollision(Entity* other)
{
	Zombie::OnCollision(other);
}

void ZombieShot::Collide(Entity* other)
{
	Zombie::Collide(other);
}

void ZombieShot::OnUpdate()
{
	Zombie::OnUpdate();

	if (GetScene<Garden>()->GetIaZombie())
	{
		IaAction();
	}
}

void ZombieShot::IaAction()
{
	if (!EUtils::IsEmptyEntityInLine<Plant>(this))
	{
		/*il y a une plante sur notre ligne*/
		if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION1); }
		else if (GetCanReload()) {/*si peut charger*/Reload(); }
	}
	else
	{
		/*il y a pas de plante sur notre ligne*/
		if (!EUtils::IsEmptyEntityInLineUp<Plant>(this))
		{
			/*il y a une plante sur la ligne du dessus*/
			if (!EUtils::IsEmptyEntityInLineDown<Plant>(this))
			{
				/*il y a une plante sur la ligne du dessus et du dessous*/
				if (GetCanShoot()) {/*on peut tirer*/
					if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/Shoot(TAGACTION3); }
					else {/*tirer dessous*/Shoot(TAGACTION5); }
				}
				else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
			}
			else
			{
				/*il y a une plante sur la ligne du dessus*/
				if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION3); }
				else if (GetCanReload()) {/*si peut charger*/Reload(); }
			}
		}
		else
		{
			/*il y a pas de plante sur notre ligne*/
			if (!EUtils::IsEmptyEntityInLineDown<Plant>(this))
			{
				/*il y a une plante sur la ligne du dessous*/
				if (GetCanShoot()) {/*on peut tirer*/Shoot(TAGACTION5); }
				else if (GetCanReload()) {/*si peut charger*/Reload(); }
			}
		}
	}
}

void ZombieShot::ActionDead()
{
	Zombie::ActionDead();
}

void ZombieShot::OnShoot(int tag)
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