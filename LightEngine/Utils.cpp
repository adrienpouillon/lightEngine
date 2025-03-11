#include <SFML/System/Vector2.hpp>
#include "Utils.h"
#include <cmath>

#include "Shot.h"
#include "Sun.h"
#include "Zombie.h"
#include "ZombieRa.h"
#include "ZombieShot.h"
#include "Peat.h"
#include "Torch.h"
#include "SunFlower.h"
#include "Mower.h"
#include "Saw.h"

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

	int LineMoreEmpty(int nbEntityInLineOne, int nbEntityInLineTwo, int nbEntityInLineThree)
	{
		bool MostlineOne = nbEntityInLineOne > 0;
		bool MostlineTwo = nbEntityInLineTwo > 0;
		bool MostlineThree = nbEntityInLineThree > 0;

		if (MostlineOne)
		{
			//line 1
			if (MostlineTwo)
			{
				//line 1 et 2
				if (MostlineThree)
				{
					//line 1 et 2 et 3
					RandomLine(3, LINEONE, HEIGHTLINE);
				}
				else
				{
					//line 1 et 2
					RandomLine(2, LINEONE, HEIGHTLINE);
				}
			}
			else
			{
				//line 1
				if (MostlineThree)
				{
					//line 1 et 3
					RandomLine(2, LINEONE, HEIGHTLINE * 2);
				}
				else
				{
					//line 1
					return LINEONE;
				}
			}
		}
		else if (MostlineTwo)
		{
			//line 2
			if (MostlineThree)
			{
				//line 2 et 3
				RandomLine(2, LINETWO, HEIGHTLINE);
			}
			else
			{
				//line 2
				return LINETWO;
			}
		}
		else if (MostlineThree)
		{
			//line 3
			return LINETHREE;
		}
		return -1;
	}

	int LineLessEntityAndMoreEmpty(int nbAllieInLineOne, int nbAllieInLineTwo, int nbAllieInLineThree, int nbEnemyInLineOne, int nbEnemyInLineTwo, int nbEnemyInLineThree)
	{
		bool MostlineOne = nbEnemyInLineOne > 0;
		bool MostlineTwo = nbEnemyInLineTwo > 0;
		bool MostlineThree = nbEnemyInLineThree > 0;

		if (MostlineOne)
		{
			//line 1
			if (MostlineTwo)
			{
				//line 1 et 2
				if (MostlineThree)
				{
					//line 1 et 2 et 3
					bool MostOne = nbAllieInLineOne > nbAllieInLineTwo;
					bool MostTwo = nbAllieInLineTwo > nbAllieInLineThree;
					bool MostThree = nbAllieInLineThree > nbAllieInLineOne;

					if (!MostOne && MostThree)
					{
						return LINEONE;
					}
					else if (!MostThree && MostTwo)
					{
						return LINETHREE;
					}
					else if (!MostTwo && MostOne)
					{
						return LINETWO;
					}
					else
					{
						RandomLine(3, LINEONE, HEIGHTLINE);
					}
				}
				else
				{
					//line 1 et 2
					bool MostOne = nbAllieInLineOne > nbAllieInLineTwo;
					bool MostTwo = nbAllieInLineTwo > nbAllieInLineOne;

					if (!MostOne)
					{
						return LINEONE;
					}
					else if (!MostTwo)
					{
						return LINETWO;
					}
					else
					{
						RandomLine(2, LINEONE, HEIGHTLINE);
					}
				}
			}
			else
			{
				//line 1
				if (MostlineThree)
				{
					//line 1 et 3
					bool MostOne = nbAllieInLineOne > nbAllieInLineThree;
					bool MostThree = nbAllieInLineThree > nbAllieInLineOne;

					if (!MostOne)
					{
						return LINEONE;
					}
					else if (!MostThree)
					{
						return LINETHREE;
					}
					else
					{
						RandomLine(2, LINEONE, HEIGHTLINE * 2);
					}
				}
				else
				{
					//line 1
					return LINEONE;
				}
			}
		}
		else if (MostlineTwo)
		{
			//line 2
			if (MostlineThree)
			{
				//line 2 et 3
				bool MostTwo = nbAllieInLineTwo > nbAllieInLineThree;
				bool MostThree = nbAllieInLineThree > nbAllieInLineTwo;

				if (!MostTwo)
				{
					return LINETWO;
				}
				else if (!MostThree)
				{
					return LINETHREE;
				}
				else
				{
					RandomLine(2, LINETWO, HEIGHTLINE);
				}
			}
			else
			{
				//line 2
				return LINETWO;
			}
		}
		else if (MostlineThree)
		{
			//line 3
			return LINETHREE;
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

namespace MUtils
{
	std::vector<Mower*> AllMowerInline(int line)
	{
		std::vector<Mower*> allMowerInLine;
		sf::Vector2i size = GameManager::Get()->GetWindowSize();
		std::vector<Mower*> allMower = EUtils::AllEntityInline<Mower>(line);
		int lenght = allMower.size();
		for (int i = 0; i < lenght; ++i)
		{
			if (allMower[i]->GetPosition().x > STARTAREACREATMOWER - 100 && allMower[i]->GetPosition().x < size.x)
			{
				allMowerInLine.push_back(allMower[i]);
			}
		}
		return allMowerInLine;
	}
}













