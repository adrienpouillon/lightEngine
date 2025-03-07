#include <SFML/System/Vector2.hpp>
#include "Utils.h"
#include <cmath>

#include "Shot.h"
#include "Sun.h"
#include "Zombie.h"
#include "Peat.h"
#include "Torch.h"
#include "SunFlower.h"
#include "Mower.h"

namespace Utils 
{
    bool Normalize(sf::Vector2f& vector)
    {
        float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;
		
			return true;
		}

		return false;
    }

	float GetDistance(int x1, int y1, int x2, int y2)
	{
		int x = x2 - x1;
		int y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}

	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		float dot = v1.x * v2.x + v1.y * v2.y;
		float det = v1.x * v2.y - v1.y * v2.x;

		return std::atan2(det, dot) * 180 / 3.14159265;
	}
}

namespace TypeUtils
{
	int TypeGroupe(int type)
	{
		if (type >= TYPEPLANT)
		{
			return TYPEPLANT;
		}
		else if (type <= TYPEZOMBIE)
		{
			return TYPEZOMBIE;
		}
		return TYPENO;
	}
}

namespace LineUtils
{
	int SeachLine(int y)
	{
		if (y > LINEONE - HEIGHTLINE / 2 && y < LINEONE + HEIGHTLINE / 2)
		{
			return LINEONE;
		}

		if (y > LINETWO - HEIGHTLINE / 2 && y < LINETWO + HEIGHTLINE / 2)
		{
			return LINETWO;
		}

		if (y > LINETHREE - HEIGHTLINE / 2 && y < LINETHREE + HEIGHTLINE / 2)
		{
			return LINETHREE;
		}

		return LINEONE;
	}

	int RandomLine(int nbLine, int firstLine, int betweenLine)
	{
		int ran = Garden::GenerateRandomNumber(1, nbLine);
		return ((ran * firstLine) + ((betweenLine - firstLine) * (ran - 1)));
	}

	int LineLessEntity(int nbEntityInLineOne, int nbEntityInLineTwo, int nbEntityInLineThree)
	{
		bool MostlineOne = nbEntityInLineOne > nbEntityInLineTwo;
		bool MostlineTwo = nbEntityInLineTwo > nbEntityInLineThree;
		bool MostlineThree = nbEntityInLineThree > nbEntityInLineOne;

		if (!MostlineOne && MostlineThree)
		{
			return LINEONE;
		}
		else if (!MostlineThree && MostlineTwo)
		{
			return LINETHREE;
		}
		else if (!MostlineTwo && MostlineOne)
		{
			return LINETWO;
		}
		return -1;
	}
}

namespace EUtils
{
	bool IsAlongLine(Entity* itMe)
	{
		return IsLineEmptyEnemy(itMe->GetTag(), itMe->GetPosition().y);
	}

	bool IsAlongLineUp(Entity* itMe)
	{
		return IsLineEmptyEnemy(itMe->GetTag(), itMe->GetPosition().y - HEIGHTLINE);
	}

	bool IsAlongLineDown(Entity* itMe)
	{
		return IsLineEmptyEnemy(itMe->GetTag(), itMe->GetPosition().y + HEIGHTLINE);
	}

	bool IsLineEmptyEnemy(int itMeType, float itMePos)
	{
		std::list<Entity*>* allEntity = GameManager::Get()->GetTabEntity();
		int itMeTypeGroupe = TypeUtils::TypeGroupe(itMeType);
		for (auto it = (*allEntity).begin(); it != (*allEntity).end(); )
		{
			if (IsEnemieInLine(itMePos, (*it)->GetPosition().y, itMeTypeGroupe, TypeUtils::TypeGroupe((*it)->GetTag())))
			{
				return false;
			}
			++it;
		}
		return true;
	}

	bool IsAreaEmpty(Entity* itMe, float area)
	{
		return IsZoneEmptyEnemy(itMe->GetTag(), itMe->GetPosition(), area);
	}

	bool IsAreaEmptyUp(Entity* itMe, float area)
	{
		return IsZoneEmptyEnemy(itMe->GetTag(), itMe->GetPosition() - sf::Vector2f(0, HEIGHTLINE), area);
	}

	bool IsAreaEmptyDown(Entity* itMe, float area)
	{
		return IsZoneEmptyEnemy(itMe->GetTag(), itMe->GetPosition() + sf::Vector2f(0, HEIGHTLINE), area);
	}

	bool IsZoneEmptyEnemy(int itMeType, sf::Vector2f itMePos, float area)
	{
		std::list<Entity*>* allEntity = GameManager::Get()->GetTabEntity();
		int itMeTypeGroupe = TypeUtils::TypeGroupe(itMeType);
		for (auto it = (*allEntity).begin(); it != (*allEntity).end(); )
		{
			if (IsEnemieInLine(itMePos.y, (*it)->GetPosition().y, itMeTypeGroupe, TypeUtils::TypeGroupe((*it)->GetTag())))//(itMePos.y == (*it)->GetPosition().y)(itMe->GetType() != (*it)->GetType())
			{
				if (itMePos.x + area > (*it)->GetPosition().x && itMePos.x - area < (*it)->GetPosition().x)
				{
					return false;
				}
			}
			++it;
		}
		return true;
	}

	bool IsEnemieInLine(float itMePos, float entityPos, int itMeType, int entityType)
	{
		if (itMePos == entityPos)
		{
			if (itMeType != entityType) { return true; }
		}
		return false;
	}

	bool IsAllieInLine(float itMePos, float entityPos, int itMeType, int entityType)
	{
		if (itMePos == entityPos)
		{
			if (itMeType == entityType) { return true; }
		}
		return false;
	}

}

namespace PUtils
{
	
}

namespace ZUtils
{

}

namespace SUtils
{
	void DecaleShot(Shot* shot, sf::Vector2f pos, float verticalDirection)
	{
		shot->SetDirectionShot(sf::Vector2f(pos.x, pos.y + verticalDirection * 2));
	}
}













