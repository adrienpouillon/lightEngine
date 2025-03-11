#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Garden.h"

class Zombie;
class Shot;
class Peat;
class Torch;
class Entity;
class Mower;

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2);
}

namespace TypeUtils
{
	int TypeGroupe(int type);
	template<typename T>
	int NbIsTagInLine(int line, int type);
}

namespace LineUtils
{
	int SeachLine(int y);
	int RandomLine(int nbLine, int firstLine, int betweenLine);

	template<typename T>
	int LineLessEntity();
	int LineLessEntity(int nbEntityInLineOne, int nbEntityInLineTwo, int nbEntityInLineThree);

	template<typename T>
	int LineMoreEmpty();
	int LineMoreEmpty(int nbEntityInLineOne, int nbEntityInLineTwo, int nbEntityInLineThree);

	int LineLessEntityAndMoreEmpty(int nbAllieInLineOne, int nbAllieInLineTwo, int nbAllieInLineThree, int nbEnemyInLineOne, int nbEnemyInLineTwo, int nbEnemyInLineThree);
}

namespace EUtils
{
	bool IsAlongLine(Entity* itMe);
	bool IsAlongLineUp(Entity* itMe);
	bool IsAlongLineDown(Entity* itMe);

	bool IsLineEmptyEnemy(int itMeType, float itMePos);


	bool IsAreaEmpty(Entity* itMe, float area);
	bool IsAreaEmptyUp(Entity* itMe, float area);
	bool IsAreaEmptyDown(Entity* itMe, float area);

	bool IsZoneEmptyEnemy(int itMeType, sf::Vector2f itMePos, float area);
	bool IsEnemieInLine(float itMePos, float entityPos, int itMeType, int entityType);
	bool IsAllieInLine(float itMePos, float entityPos, int itMeType, int entityType);

	template<typename T>
	bool IsEmptyEntityInLine(Entity* itMe);
	template<typename T>
	bool IsEmptyEntityInLineUp(Entity* itMe);
	template<typename T>
	bool IsEmptyEntityInLineDown(Entity* itMe);

	template<typename T>
	bool IsLineEmptyEntity(float itMePos);
	template<typename T>
	bool IsCollumEmptyEntity(float itMePos);

	template<typename T>
	bool IsZoneEmptyEntity(sf::Vector2f itMePos, float area);
	template<typename T>
	bool IsEntityInLine(float itMePos, float entityPos, Entity* entity);
	template<typename T>
	std::vector<T*> AllEntityInline(int line);
	template<typename T>
	inline int NbEntityInLine(int line);
}

namespace PUtils
{

}

namespace ZUtils
{

}

namespace SUtils
{
	void DecaleShot(Shot* shot, sf::Vector2f pos, float verticalDirection);
}

namespace MUtils
{
	std::vector<Mower*> AllMowerInline(int line);
}

namespace TypeUtils
{
	template<typename T>
	inline int NbIsTagInLine(int line, int type)
	{
		std::vector<T*> allEntity = EUtils::AllEntityInline<T>(line);
		int nbHaveTag = 0;
		int lenght = (int)allEntity.size();
		for (int i = 0; i < lenght; ++i)
		{
			if (allEntity[i].GetType() == type)
			{
				nbHaveTag++;
			}
		}
		return nbHaveTag;
	}
}

namespace LineUtils
{
	template<typename T>
	inline int LineLessEntity()
	{
		return LineLessEntity(EUtils::NbEntityInLine<T>(LINEONE), EUtils::NbEntityInLine<T>(LINETWO), EUtils::NbEntityInLine<T>(LINETHREE));
	}

	template<typename T>
	inline int LineMoreEmpty()
	{
		return LineMoreEmpty(EUtils::NbEntityInLine<T>(LINEONE), EUtils::NbEntityInLine<T>(LINETWO), EUtils::NbEntityInLine<T>(LINETHREE));
	}
}

namespace EUtils
{
	template<typename T>
	inline bool IsEmptyEntityInLine(Entity* itMe)
	{
		return IsLineEmptyEntity<T>(itMe->GetPosition().y);
	}

	template<typename T>
	inline bool IsEmptyEntityInLineUp(Entity* itMe)
	{
		return IsLineEmptyEntity<T>(itMe->GetPosition().y - HEIGHTLINE);
	}

	template<typename T>
	inline bool IsEmptyEntityInLineDown(Entity* itMe)
	{
		return IsLineEmptyEntity<T>(itMe->GetPosition().y + HEIGHTLINE);
	}

	template<typename T>
	inline bool IsLineEmptyEntity(float itMePos)
	{
		std::list<Entity*>* allEntity = GameManager::Get()->GetTabEntity();
		for (auto it = (*allEntity).begin(); it != (*allEntity).end(); )
		{
			if (IsEntityInLine<T>(itMePos, (*it)->GetPosition().y, *it))
			{
				return false;
			}
			++it;
		}
		return true;
	}

	template<typename T>
	inline bool IsCollumEmptyEntity(float itMePos)
	{
		std::list<Entity*>* allEntity = GameManager::Get()->GetTabEntity();
		for (auto it = (*allEntity).begin(); it != (*allEntity).end(); )
		{
			if (IsEntityInLine<T>(itMePos, (*it)->GetPosition().x, *it))
			{
				return false;
			}
			++it;
		}
		return true;
	}

	template<typename T>
	inline bool IsZoneEmptyEntity(sf::Vector2f itMePos, float area)
	{
		std::list<Entity*>* allEntity = GameManager::Get()->GetTabEntity();
		for (auto it = (*allEntity).begin(); it != (*allEntity).end(); )
		{
			if (IsEntityInLine<T>(itMePos.y, (*it)->GetPosition().y, *it))//(itMePos.y == (*it)->GetPosition().y)(itMe->GetType() != (*it)->GetType())
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

	template<typename T>
	inline bool IsEntityInLine(float itMePos, float entityPos, Entity* entity)
	{
		if (itMePos == entityPos)
		{
			if (Garden::GetTypeConvert<T*>(entity))
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline std::vector<T*> AllEntityInline(int line)
	{
		std::vector<T*> allEntityInLine;
		std::vector<T*> allEntity = Garden::GetAllTypeConvert<T>(*GameManager::Get()->GetTabEntity());
		int lenght = allEntity.size();
		for (int i = 0; i < lenght; ++i)
		{
			if (allEntity[i]->GetPosition().y > line - HEIGHTLINE / 3 && allEntity[i]->GetPosition().y < line + HEIGHTLINE / 3)
			{
				allEntityInLine.push_back(allEntity[i]);
			}
		}
		return allEntityInLine;
	}

	template<typename T>
	inline int NbEntityInLine(int line)
	{
		std::vector<T*> allZombie = EUtils::AllEntityInline<T>(line);
		return (int)allZombie.size();
	}
}

namespace MUtils
{
	
}

/*template<typename T>
inline bool IsEntityHaveTypeInLine(float itMePos, float entityPos, int type, int entityType)
{
	if (itMePos == entityPos)
	{
		if (type == entityType)
		{
			return true;
		}
	}
	return false;
}*/