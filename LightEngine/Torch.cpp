#include "Torch.h"
#include "Zombie.h"
#include "Shot.h"

void Torch::OnInitialize()
{
	Plant::OnInitialize();
	SetTag(TYPEPLANTTORCH);
}

void Torch::OnCollision(Entity* other)
{
	if (other->GetTag() <= TYPEZOMBIE)
	{
		Alive::LifeLessLess();
	}
	else if (Shot* shot = Garden::GetTypeConvert<Shot*>(other))
	{
		int type = shot->GetTag();
		if (type >= TYPEPLANT)
		{
			mShot = shot;
		}
	}
	SetIsCollide(true);
}

void Torch::OnUpdate()
{
	Plant::OnUpdate();
}

void Torch::ActionDead()
{
	Plant::ActionDead();
	GetScene<Garden>()->InstanceShotRoc(this, MYLINE, GetPosition(), (GetRadius() * 3) / 4);
}

void Torch::IaAction()
{
	if (mShot != nullptr) {
		bool noPlantUp = EUtils::IsEmptyEntityInLineUp<Plant>(this);
		bool noPlantDown = EUtils::IsEmptyEntityInLineDown<Plant>(this);
		if (!EUtils::IsAlongLine(this)) {/*il y a un enemie*/
			if (noPlantUp)
			{
				/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
				if (noPlantDown)
				{
					/*il y a un enemie sur notre ligne mais pas de plante au dessus et au dessous*/
					EnemyAlmost(TAGACTION2, TAGACTION1, TAGACTION6, TAGACTION8);
				}
				else
				{
					/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
					EnemyAlmost(TAGACTION2, TAGACTION1, TAGACTION6, TAGACTION7);
				}
			}
			else
			{
				/*il y a un enemie sur notre ligne avec une plante au dessus*/
				if (noPlantDown)
				{
					/*il y a un enemie sur notre ligne mais pas de plante au dessous*/
					EnemyAlmost(TAGACTION2, TAGACTION1, TAGACTION5, TAGACTION8);
				}
				else
				{
					EnemyAlmost(TAGACTION2, TAGACTION1, TAGACTION5, TAGACTION7);
				}
			}
		}
		else
		{
			/*il y a pas d'enemie*/
			if (noPlantUp)
			{
				/*il y a pas d'enemie sur notre ligne mais pas de plante au dessus*/
				if (noPlantDown)
				{
					/*il y a pas d'enemie sur notre ligne mais pas de plante au dessus et au dessous*/
					if (!IsLineUpDownHaveDanger(TAGACTION3, TAGACTION4))
					{
						/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
						if (GetCanBoost()) {/*on peut booster*/
							if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*booster dessus*/Boost(TAGACTION3); }
							else {/*booster dessous*/Boost(TAGACTION4); }
						}
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
				else
				{
					/*il y a pas d'enemie sur notre ligne mais pas de plante au dessus*/
					if (!EnemyInLineUpDown(TAGACTION3, TAGACTION4))
					{
						/*il y a pas d'enemie sur la ligne du dessus et du dessous*/
						if (!IsLineUpDownHaveDanger(TAGACTION3, TAGACTION4))
						{
							/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
							if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
				}
			}
			else
			{
				/*il y a pas d'enemie sur notre ligne mais pas de plante au dessous*/
				if (noPlantDown)
				{
					/*il y a pas d'enemie sur notre ligne mais pas de plante au dessus et au dessous*/
					if (!IsLineUpDownHaveDanger(TAGACTION3, TAGACTION4))
					{
						/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
						if (!IsLineUpDownHaveDanger(TAGACTION3, TAGACTION4))
						{
							/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
							if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
				}
				else
				{
					/*il y a pas d'enemie sur notre ligne*/
					if (!IsLineUpDownHaveDanger(TAGACTION3, TAGACTION4))
					{
						/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
						if (!EnemyInLineUpDown(TAGACTION3, TAGACTION4))
						{
							/*il y a pas d'enemie sur la ligne du dessus et du dessous*/
							if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
				}
			}
		}
		mShot = nullptr;
	}
	else
	{
		if (GetCanReload()) {/*on peut recharger*/Reload(); }
	}
}

void Torch::EnemyAlmost(int tagAlmost, int tagFar, int tagUp, int tagDown)
{
	if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
	{
		/*il y a un enemie proche*/
		if (GetCanBoost()) {/*on peut booster*/Boost(tagAlmost); }
		else if (GetCanReload()) {/*on peut recharger*/Reload(); }
	}
	else
	{
		/*il y a un enemie pas proche*/
		if (!IsLineUpDownHaveDanger(tagUp, tagDown))
		{
			/*il y a un enemie pas proche sur la ligne du dessus et du dessous*/
			if (GetCanBoost()) {/*on peut booster*/Boost(tagFar); }
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
	}
}

bool Torch::IsLineUpDownHaveDanger(int tagUp, int tagDown)
{
	if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5))
	{
		/*il y a un enemie proche sur la ligne du dessus*/
		if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
		{
			/*il y a un enemie proche sur la ligne du dessus et du dessous*/
			if (GetCanBoost()) {/*on peut booster*/
				if (Garden::GenerateRandomNumber(0, 1) == 0) {/*booster dessus*/Boost(tagUp); }
				else {/*booster dessous*/Boost(tagDown); }
			}
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
		else
		{
			/*il y a un enemie proche sur la ligne du dessus*/
			if (GetCanBoost()) {/*on peut booster*/Boost(tagUp); }
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
	}
	else
	{
		/*il y a pas d'enemie proche sur la ligne du dessus*/
		if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
		{
			/*il y a un enemie proche sur la ligne du dessous*/
			if (GetCanBoost()) {/*on peut booster*/Boost(tagDown); }
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
		else
		{
			/*il y a pas d'enemie proche sur la ligne du dessous*/
			return false;
		}
	}
	return true;
}

bool Torch::EnemyInLineUpDown(int tagUp, int tagDown)
{
	if (!EUtils::IsAlongLineUp(this))
	{
		/*il y a un enemie sur la ligne du dessus*/
		if (!EUtils::IsAlongLineDown(this))
		{
			/*il y a un enemie sur la ligne du dessus et du dessous*/
			if (GetCanBoost()) {/*on peut booster*/
				if (GetScene()->GenerateRandomNumber(0, 1) == 0) {/*booster dessus*/Boost(tagUp); }
				else {/*booster dessous*/Boost(tagDown); }
			}
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
		else
		{
			/*il y a un enemie sur la ligne du dessus*/
			if (GetCanBoost()) {/*on peut booster*/Boost(tagUp); }
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
	}
	else
	{
		/*il y a un enemie pas d'enemie sur la ligne du dessus*/
		if (!EUtils::IsAlongLineDown(this))
		{
			/*il y a un enemie sur la ligne du dessous*/
			if (GetCanBoost()) {/*on peut booster*/Boost(tagDown); }
			else if (GetCanReload()) {/*on peut recharger*/Reload(); }
		}
		else
		{
			/*il y a pas d'enemie sur la ligne du dessus et du dessous*/
			return false;
		}
	}
	return true;
}

void Torch::OnBoost(int tag)
{
	Garden* garden = GetScene<Garden>();
	switch (tag)
	{
	case TAGACTION1:
	{
		//dupliquer un shot
		sf::Vector2f pos = GetPosition();
		garden->InstanceShot(this, MYLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShot(this, MYLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		break;
	}
	case TAGACTION2:
	{
		//dupliquer un super shot
		sf::Vector2f pos = GetPosition();
		garden->InstanceShotRoc(this, MYLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShotRoc(this, MYLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		AmmoLessLess();
		break;
	}
	case TAGACTION3:
	{
		//decaler un shot sur la ligne du dessus
		sf::Vector2f pos = mShot->GetPosition();
		SUtils::DecaleShot(mShot, pos, UPLINE);
		break;
	}
	case TAGACTION4:
	{
		//decaler un shot sur la ligne du dessous
		sf::Vector2f pos = mShot->GetPosition();
		SUtils::DecaleShot(mShot, pos, DOWNLINE);
		break;
	}
	case TAGACTION5:
	{
		//dupliquer et decaler un shot sur la ligne du dessus
		sf::Vector2f pos = GetPosition();
		garden->InstanceShot(this, UPLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShot(this, UPLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		break;
	}
	case TAGACTION6:
	{
		//dupliquer et decaler un shot sur la ligne du dessus
		sf::Vector2f pos = GetPosition();
		garden->InstanceShotRoc(this, UPLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShotRoc(this, UPLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		AmmoLessLess();
		break;
	}
	case TAGACTION7:
	{
		//dupliquer et decaler un shot sur la ligne du dessous
		sf::Vector2f pos = GetPosition();
		garden->InstanceShot(this, DOWNLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShot(this, DOWNLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		break;
	}
	case TAGACTION8:
	{
		//dupliquer et decaler un shot sur la ligne du dessous
		sf::Vector2f pos = GetPosition();
		garden->InstanceShotRoc(this, DOWNLINE, sf::Vector2f(pos.x - GetRadius(), pos.y));
		garden->InstanceShotRoc(this, DOWNLINE, sf::Vector2f(pos.x - GetRadius() * 2, pos.y));
		AmmoLessLess();
		break;
	}
	}
}