#include "CristalLight.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"
#include "Sun.h"
#include "Debug.h"

void CristalLight::OnInitialize()
{
	Plant::OnInitialize();
	SetTag(TYPEPLANTPEAT);
	mCoin = 0;
}

void CristalLight::OnCollision(Entity* other)
{
	int tag = other->GetTag();
	if (tag <= TYPEZOMBIE)
	{
		Alive::LifeLessLess();
	}
	else if (tag == TYPESUN)
	{
		if (Sun* sun = Garden::GetTypeConvert<Sun*>(other))
		{
			sun->ActionDead();
			float coef = (float)sun->GetRadius() / (float)SUNRADIUS;
			mCoin += 20 * coef * coef;
		}
	}
	SetIsCollide(true);
}

void CristalLight::OnUpdate()
{
	Plant::OnUpdate();
	
	Garden* garden = GetScene<Garden>();
	if (garden->GetIaPlantCreat())
	{
		MoreCoin();
	}

	sf::Vector2f pos = GetPosition();
	std::string stringCoin = std::to_string(mCoin) + " S";
	Debug::DrawText(pos.x, pos.y, stringCoin, 0.5f, 0.5f, sf::Color::Black);
}

void CristalLight::MoreCoin()
{
	mTimeSunProgress -= GetDeltaTime();
	if (mTimeSunProgress < 0.f)
	{
		if (mCoin < 500)
		{
			Garden* garden = GetScene<Garden>();
			int coin = garden->GetPlantCoin();
			int nb = 0;
			if (coin > 400)
			{
				nb = 25;
				mTimeSunProgress = 4.f;
			}
			else if (coin > 0)
			{
				nb = 1;
				mTimeSunProgress = 1.f;
			}
			else
			{
				mTimeSunProgress = 1.f;
				return;
			}
			garden->IncreasePlantCoin(-nb);
			mCoin += nb;
		}
	}
}

void CristalLight::IaAction()
{/*si peut reload*/
	if (!GetCanReload()){/*si peut pas reload et si peut shoot*/
		if (GetCanShoot()){/*si peut shoot et a plus de 10 coin*/
			if (mCoin < COSTSHOT){	return;}
		}else{return;}
	}

 	bool noPlantUp = EUtils::IsEmptyEntityInLineUp<Plant>(this);
	bool noPlantDown = EUtils::IsEmptyEntityInLineDown<Plant>(this);
	if (EUtils::IsAlongLine(this) == false) {/*il y a un enemie*/
		if (noPlantUp){/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
			if (noPlantDown){/*il y a un enemie sur notre ligne mais pas de plante au dessus et au dessous*/
				if (!EUtils::IsAreaEmpty(this, GetRadius() * 5)){/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*2, LIFESHOT*8, MYLINE, COSTSHOT*10 }; Shoot(TAGACTION3); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}else{/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, MYLINE, COSTSHOT*8 }; Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}
					}else{/*il y a un enemie proche sur notre ligne*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, MYLINE, COSTSHOT*8 }; Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
						}else{/*il y a un enemie proche sur notre ligne mais pas de plante au dessus et au dessous*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, MYLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
				else if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
					if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessus et dessous mais pas de plante au dessous et au dessous*/
						if (GetCanShoot()) {/*on peut tirer*/
							if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, UPLINE, COSTSHOT*8 }; Shoot(TAGACTION2); }
							else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, DOWNLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
						}
						else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
					}else{/*il y a un enemie proche sur la ligne du dessus mais pas de plante au dessus*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, UPLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}
				else if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie proche sur la ligne du dessous mais pas de plante au dessous*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, DOWNLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
					else if (GetCanReload()) {/*si peut super charger*/Reload(); }
				}else{/*il y a un enemie pas proche sur notre ligne et celle du dessus et celle du dessous mais pas de plante au dessus ou au dessous*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, MYLINE, COSTSHOT*2 }; Shoot(TAGACTION2); }
					else if (GetCanReload()) {/*si peut super charger*/Reload(); }
				}
			}else{/*il y a un enemie sur notre ligne mais pas de plante au dessus*/
				if (!EUtils::IsAreaEmpty(this, GetRadius() * 5)){/*si enemie proche sur notre ligne*/
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*si enemie proche sur notre ligne et celle du dessus*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT * 4, MYLINE, COSTSHOT * 6 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}else{/*si enemie proche sur notre ligne*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, MYLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}else{/*si enemie pas proche sur notre ligne*/
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*si enemie proche sur la ligne du dessus*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
					}else{/*si enemie pas proche sur la ligne du dessus*/
						if (!EUtils::IsAlongLineUp(this)){/*si enemie sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, MYLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
							}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}else{/*si pas enemie sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, MYLINE, COSTSHOT }; Shoot(TAGACTION1); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
			}
		}else{/*il y a un enemie sur notre ligne*/
			if (noPlantDown){/*il y a un enemie sur notre ligne mais pas de plante au dessous*/
				if (!EUtils::IsAreaEmpty(this, GetRadius() * 5)){/*si enemie proche sur notre ligne*/
					if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5))
					{/*si enemie proche sur notre ligne et celle du dessous*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, MYLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}else{/*si enemie proche sur notre ligne*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, MYLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/Reload(); }
					}
				}else{/*si enemie pas proche sur notre ligne*/
					if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*si enemie proche sur la ligne du dessous*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
					}else{/*si enemie pas proche sur la ligne du dessous*/
						if (!EUtils::IsAlongLineDown(this)){/*si enemie sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, MYLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
							}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}else{/*si pas enemie sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, MYLINE, COSTSHOT }; Shoot(TAGACTION1); }
							else if (GetCanReload()) {/*si peut super charger*/Reload(); }
						}
					}
				}
			}else{/*il y a un enemie sur notre ligne*/
				if (!EUtils::IsAreaEmpty(this, GetRadius() * 5)) {/*si enemie proche*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, MYLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
					else if (GetCanReload()) {/*si peut super charger*/SuperReload(); }
				}else{/*si pas d'enemie proche*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, MYLINE, COSTSHOT }; Shoot(TAGACTION1); }
					else if (GetCanReload()) {/*si peut recharger*/Reload(); }
				}
			}
		}
	}
	else
	{/*il y a personne sur notre ligne*/
		bool enemieUp = !EUtils::IsAlongLineUp(this);
		bool enemieDown = !EUtils::IsAlongLineDown(this);
		if (enemieUp && enemieDown) {/*il y a un enemie sur la ligne du dessus et du dessous*/
			if (noPlantUp){/*il y a un enemie sur la ligne du dessus et du dessous mais pas de plante au dessus*/
				if (noPlantDown){/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessus proche*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessus proche + un enemie sur la ligne du dessous proche*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, UPLINE, COSTSHOT*8 }; Shoot(TAGACTION2); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS*5 / 4, LIFESHOT*6, DOWNLINE, COSTSHOT*8 }; Shoot(TAGACTION2); }
							}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}else{/*il y a un enemie sur la ligne du dessus proche*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, UPLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}else{/*il y a un enemie sur la ligne du dessus mais pas proche*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessous proche*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS, LIFESHOT*4, DOWNLINE, COSTSHOT*6 }; Shoot(TAGACTION2); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}else{/*il y a un enemie sur la ligne du dessous mais pas proche*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT, UPLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
							}else if (GetCanReload()) {/*on peut recharger*/SuperReload(); }
						}
					}
				}else{/*il y a un enemie sur la ligne du dessous avec une plante donc tire dessus*/ ////////////////////////////////
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessus proche*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}else{/*il y a un enemie sur la ligne du dessus mais pas de plante*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}
			}else{/*il y a un enemie sur la ligne du dessus avec une plante*/
				if (noPlantDown){/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessous proche*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}else{/*il y a un enemie sur la ligne du dessous mais pas proche*/
						if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
						else if (GetCanReload()) {/*on peut recharger*/Reload(); }
					}
				}else{/*il y a un enemie sur la ligne du dessous avec une plante*/
					if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessus proche*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tuer un max enemie sur la ligne du dessus ou dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, UPLINE, COSTSHOT }; Shoot(TAGACTION1); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, DOWNLINE, COSTSHOT }; Shoot(TAGACTION1); }
							}else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, UPLINE, COSTSHOT }; Shoot(TAGACTION1); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}else {/*il y a un enemie sur la ligne du dessus mais pas proche*/
						if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)) {/*il y a un enemie sur la ligne du dessous proche donc tirer sur la ligne du dessous*/
							if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, DOWNLINE, COSTSHOT }; Shoot(TAGACTION1); }
							else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}else {/*il y a un enemie sur la ligne du dessous mais pas proche donc tirer sur la ligne du dessus ou dessous*/
							if (GetCanShoot()) {/*on peut tirer*/
								if (Garden::GenerateRandomNumber(0, 1) == 0) {/*tirer dessus*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, UPLINE, COSTSHOT }; Shoot(TAGACTION1); }
								else {/*tirer dessous*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, DOWNLINE, COSTSHOT }; Shoot(TAGACTION1);}
							}else if (GetCanReload()) {/*on peut recharger*/Reload(); }
						}
					}
				}
			}
		}else if (enemieUp){/*il y a un enemie sur la ligne du dessus*/
			if (noPlantUp){/*il y a un enemie sur la ligne du dessus mais pas de plante*/
				if (!EUtils::IsAreaEmptyUp(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessus proche*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}else{/*il y a un enemie sur la ligne du dessus mais pas de plante*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, UPLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}else{/*il y a un enemie sur la ligne du dessus et une plante*/
				if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS / 2, LIFESHOT, UPLINE, COSTSHOT }; Shoot(TAGACTION1); }
				else if (GetCanReload()) {/*on peut recharger*/Reload(); }
			}
		}else if (enemieDown) {/*il y a un enemie sur la ligne du dessous*/
			if (noPlantDown){/*il y a un enemie sur la ligne du dessous mais pas de plante*/
				if (!EUtils::IsAreaEmptyDown(this, GetRadius() * 5)){/*il y a un enemie sur la ligne du dessous proche*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*4 }; Shoot(TAGACTION2); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}else{/*il y a un enemie sur la ligne du dessous mais pas de plante*/
					if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS*3 / 4, LIFESHOT*2, DOWNLINE, COSTSHOT*2 }; Shoot(TAGACTION1); }
					else if (GetCanReload()) {/*on peut recharger*/Reload(); }
				}
			}else{/*il y a un enemie sur la ligne du dessous avec une plante*/
				if (GetCanShoot()) {/*on peut tirer*/mShotVarible = { ENTITYRADIUS/2, LIFESHOT, DOWNLINE, COSTSHOT};Shoot(TAGACTION1); }
				else if (GetCanReload()) {/*on peut recharger*/Reload(); }
			}
		}
		else if (GetCanReload()) {/*on peut super charger*/SuperReload(); }
	}
}

void CristalLight::OnShoot(int tag)
{
	Garden* garden = GetScene<Garden>();
	switch (tag)
	{
	case TAGACTION1:
		//tirer une shot
		garden->CreatShot(mShotVarible.mRadius, sf::Color::Yellow, GetPosition(), false, mShotVarible.mLife, TYPEPLANT, mShotVarible.mLine);
		mCoin -= mShotVarible.mCost;
		break;
	case TAGACTION2:
		//super tirer une shot
		garden->CreatShot(mShotVarible.mRadius, sf::Color::Magenta, GetPosition(), false, mShotVarible.mLife * 20, TYPEPLANT, mShotVarible.mLine);
		mCoin -= mShotVarible.mCost * 2; 
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGACTION3:
		//super tirer une shot
		garden->CreatShot(mShotVarible.mRadius, sf::Color::Red, GetPosition(), false, mShotVarible.mLife * 30, TYPEPLANT, UPLINE);
		garden->CreatShot(mShotVarible.mRadius, sf::Color::Red, GetPosition(), false, mShotVarible.mLife * 30, TYPEPLANT, MYLINE);
		garden->CreatShot(mShotVarible.mRadius, sf::Color::Red, GetPosition(), false, mShotVarible.mLife * 30, TYPEPLANT, DOWNLINE);
		mCoin -= mShotVarible.mCost * 4;
		AmmoLessLess();
		AmmoLessLess();
		AmmoLessLess();
		AmmoLessLess();
		break;
	case TAGACTION4:
		
		break;
	case TAGACTION5:
		
		break;
	case TAGACTION6:
		
		break;
	case TAGACTION7:
		
		break;
	case TAGACTION8:
		
		break;
	}
}

void CristalLight::IncreaseCoin(int coin)
{
	mCoin = coin;
}

int CristalLight::GetCoin()
{
	return mCoin;
}