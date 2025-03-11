#include "SunFlower.h"
#include "Garden.h"
#include "Zombie.h"
#include "Shot.h"

void SunFlower::OnInitialize()
{
	Plant::OnInitialize();
	SetTag(TYPEPLANTSUNFLOWER);
}

void SunFlower::OnCollision(Entity* other)
{
	if (other->GetTag() <= TYPEZOMBIE)
	{
		Alive::LifeLessLess();
	}
	/*if (Garden::GetTypeConvert<Zombie*>(other))
	{
		Alive::LifeLessLess();
	}
	else if (Shot* shot = Garden::GetTypeConvert<Shot*>(other))
	{
		if (shot->GetType() <= TYPEZOMBIE)
		{
			Alive::LifeLessLess();
		}
	}*/
	SetIsCollide(true);
}

void SunFlower::OnUpdate()
{
	Plant::OnUpdate();
}

void SunFlower::ActionDead()
{
	Plant::ActionDead();
}

void SunFlower::IaAction()
{
	if (GetCanBoost() || GetCanReload())
	{
		Garden* garden = GetScene<Garden>();
		bool noPlantUp = EUtils::IsEmptyEntityInLineUp<Plant>(this);
		bool noPlantDown = EUtils::IsEmptyEntityInLineDown<Plant>(this);
		if (garden->GetPlantCoin() < 0)
		{
			/*il y a moins de 0 soleil*/
			if (noPlantUp && noPlantDown)
			{
				/*il y a pas de plante au dessus et en desssous*/
				if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
				{
					if (GetCanBoost()){/*on peut booster*/Boost(TAGACTION6);}
					else if (GetCanReload()) {/*on peut super recharger*/SuperReload(); }
				}
				else
				{
					if (GetCanBoost()){/*on peut tirer*/Boost(TAGACTION5);}
					else if (GetCanReload()) {/*on peut super recharger*/SuperReload(); }
				}
			}
			else
			{
				/*il y a pas de plante au dessus*/
				IsAreaEmptyAction(TAGACTION3, TAGACTION4);
			}
		}
		else
		{
			/*il y a plus de 0 soleil*/
			if (noPlantUp && noPlantDown)
			{
				/*il y a pas de plante au dessus et en desssous*/
				if (garden->GetPlantCoin() < 500){IsAreaEmptyAction(TAGACTION2, TAGACTION4);}
				else{IsAreaEmptyAction(TAGACTION3, TAGACTION4);}
			}
			else
			{
				/*il y a une plante au dessous et en desssous*/
				IsAreaEmptyAction(TAGACTION1, TAGACTION2);
			}
		}
	}
}

void SunFlower::IsAreaEmptyAction(int tagEmpty, int tagNoEmpty)
{
	if (!EUtils::IsAreaEmpty(this, GetRadius() * 5))
	{
		if (GetCanBoost()) {/*on peut booster*/Boost(tagNoEmpty); }
		else if (GetCanReload()) {/*on peut recharger*/Reload(); }
	}
	else
	{
		if (GetCanBoost()) {/*on peut booster*/Boost(tagEmpty); }
		else if (GetCanReload()) {/*on peut recharger*/Reload(); }
	}
}

void SunFlower::OnBoost(int tag)
{
	Garden* garden = GetScene<Garden>();
	switch (tag)
	{
	case TAGACTION1:
	{
		//creer un sun
		sf::Vector2f pos = GetPosition();
		sf::Vector2f ran = MoreLessWithRadius();
		garden->InstanceSun(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		break;
	}
	case TAGACTION2:
	{
		//creer un double sun
		sf::Vector2f pos = GetPosition();
		sf::Vector2f ran = MoreLessWithRadius();
		garden->InstanceSunDouble(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		AmmoLessLess();
		break;
	}
	case TAGACTION3:
	{
		//creer deux sun
		sf::Vector2f pos = GetPosition();
		sf::Vector2f ran;
		ran = MoreLessWithRadius();
		garden->InstanceSun(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		ran = MoreLessWithRadius();
		garden->InstanceSun(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		break;
	}
	case TAGACTION4:
	{
		//creer deux double sun
		sf::Vector2f pos = GetPosition();
		sf::Vector2f ran;
		ran = MoreLessWithRadius();
		garden->InstanceSunDouble(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		AmmoLessLess();
		ran = MoreLessWithRadius();
		garden->InstanceSunDouble(sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + ran.x, pos.y + ran.y));
		AmmoLessLess();
		break;
	}
	case TAGACTION5:
	{
		sf::Vector2i size  = GameManager::Get()->GetWindowSize();
		sf::Vector2f min = sf::Vector2f(0.f, (float)-size.y);
		sf::Vector2f max = sf::Vector2f((float)size.x, 0.f);
		int ranI = Garden::GenerateRandomNumber(5, 20);
		for (int i = 0; i < ranI; i++)
		{
			sf::Vector2f ran = Garden::MoreLess(min, max);
			garden->InstanceSun(sf::Vector2f(ran.x, ran.y));
			if (i % 5 == 0)
			{
				AmmoLessLess();
				AmmoLessLess();
			}
		}
		break;
	}
	case TAGACTION6:
	{
		sf::Vector2i size = GameManager::Get()->GetWindowSize();
		sf::Vector2f min = sf::Vector2f(0.f, (float)-size.y);
		sf::Vector2f max = sf::Vector2f((float)size.x, 0.f);
		int ranI = Garden::GenerateRandomNumber(5, 20);
		for (int i = 0; i < ranI; i++)
		{
			sf::Vector2f ran = Garden::MoreLess(min, max);
			if (Garden::GenerateRandomNumber(0, 2) == 0)
			{
				garden->InstanceSun(sf::Vector2f(ran.x, ran.y));
			}
			else
			{
				garden->InstanceSunDouble(sf::Vector2f(ran.x, ran.y));
			}
			
			if (i % 5 == 0)
			{
				AmmoLessLess();
				AmmoLessLess();
			}
		}
		break;
	}
	case TAGACTION7:
	{
		
		break;
	}
	case TAGACTION8:
	{
		
		break;
	}
	}
}

sf::Vector2f SunFlower::MoreLessWithRadius()
{
	float radius = GetRadius() * 2;
	return Garden::MoreLess(sf::Vector2f (-radius, -radius), sf::Vector2f(radius, radius));
}