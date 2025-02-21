#pragma once
#include "Scene.h"
#include "Mouse.h"

#define ENTITYRADIUS 50 

#define COLLUMPLANT ENTITYRADIUS*2
#define COLLUMZOMBIE 1350
#define HEIGHTLINE 250
#define LINEONE 100
#define LINETWO HEIGHTLINE + LINEONE
#define LINETHREE HEIGHTLINE + LINETWO

#define LIFEPLANT 3
#define LIFESHOT 3
#define LIFESHOTROC 3
#define LIFEZOMBIE 3
#define LIFEZOMBIECONE 3
#define LIFEZOMBIESPORT 3

#define SPEEDZOMBIE 20.f

#define CREATELOW 1.5f
#define CREATENORMAL 0.8f
#define CREATEFAST 0.4f
#define CREATEAPPOCALYPSE 0.1f
#define CREATENOSTOP 0.f

#define MODEZOMBIE 0
#define MODEPLANT MODEZOMBIE + 1

#define MAXMODECREATOR MODEPLANT + 1

class Garden :public Scene
{
protected:
	std::list<Entity*>* mAllEntity;
	int mModeCreator;
	sf::Vector2f mMousePos;
	Mouse* mMouse;
	int mZombiePass;
	int mZombieDestroy;
	bool mIaZombie;
	bool mIaPlant;
	float mTimeZombieCreat;
	float mTimeZombieCreatProgress;
public:
	void OnInitialize();

	void CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type, float verticalDirection);

	void CreatZombie(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);

	void CreatZombieCone(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);

	void CreatZombieSport(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);

	void CreatPlant(float radius, sf::Vector2f pos, bool rigidBody, int life);

	void OnEvent(const sf::Event& event);

	void OnEventMouse(const sf::Event& event);

	void OnEventKeyboard(const sf::Event& event);

	void OnUpdate();

	bool TryShot(Entity* pEntity, float x, float y);

	bool TryShotRoc(Entity* pEntity, float x, float y);

	void InstanceShot(Entity* itsCreator, float verticalDirection);

	void InstanceShotRoc(Entity* itsCreator, float verticalDirection);

	int SeachLine(int y);

	bool IsAlongLine(Entity* itMe);

	bool IsAlongLineDown(Entity* itMe);

	bool IsAlongLineUp(Entity* itMe);

	bool IsLineEmptyEnemy(int itMeType, float itMePos);

	bool IsAreaEmpty(Entity* itMe, float area);

	bool IsAreaEmptyUp(Entity* itMe, float area);

	bool IsAreaEmptyDown(Entity* itMe, float area);

	bool IsZoneEmptyEnemy(int itMeType, sf::Vector2f itMePos, float area);

	bool IsEnemieInLine(float itMePos, float entityPos, int itMeType, int entityType);

	bool IsAllieInLine(float itMePos, float entityPos, int itMeType, int entityType);

	bool IsEmptyPlantInLine(Entity* itMe);

	bool IsEmptyPlantInLineUp(Entity* itMe);

	bool IsEmptyPlantInLineDown(Entity* itMe);

	bool IsLineEmptyPlant(float itMePos);

	bool IsPlantInLine(float itMePos, float entityPos, Entity* entity);

	bool IsZoneEmptyPlant(sf::Vector2f itMePos, float area);

	int NbPlantInLine(int line);

	void CreatNewPlant(float radius, bool rigidBody, int life, int line);

	int RandomLine(int nbLine);

	void IaAction();

	void SetTimeCreat(float time);

	float GetTimeCreat();

	bool GetIaZOMBIE();

	bool GetIaPlant();

	template<typename T>
	T* GetEntity();

	template<typename T>
	std::vector<T*> GetAllEntity();

	template<typename T, typename A>
	T GetTypeConvert(A TypeA);

	template<typename T, typename A>
	std::vector<T*> GetAllTypeConvert(std::vector<A*> tabTypeA);

	template<typename T, typename A>
	std::vector<T*> GetAllTypeConvert(std::list<A*> tabTypeA);

	template<typename T, typename A>
	std::vector<T*> GetConvertVector(std::vector<A*> tabTypeA);

	template<typename T>
	bool VectorIsEmpty(std::vector<T*> tabTypeA);

	template<typename T>
	std::vector<T*> AllEntityInline(int line);

	void SetMousePosition(sf::Vector2f mousePos);

	sf::Vector2f GetMousePosition();

	void SetModeCreator(int modeCreator);

	int GetModeCreator();

	void IncreaseZombiePass();

	int GetZombiePass();

	void IncreaseZombieDestroy();

	int GetZombieDestroy();

};

template<typename T>
inline T* Garden::GetEntity()
{
	for (int i = 0; i < mAllEntity.size(); ++i)
	{
		if (T* entity = dynamic_cast<T*>(mAllEntity[i]))
		{
			return entity;
		}
	}
	return nullptr;
}

//si modifier voir aussi la fonction constante
template<typename T>
inline std::vector<T*> Garden::GetAllEntity()
{
	std::vector<T*> allT;
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (T* entity = dynamic_cast<T*>(*it))
		{
			allT.push_back(entity);
		}
		++it;
	}
	return allT;
}

template<typename T, typename A>
inline T Garden::GetTypeConvert(A TypeA)
{
	if (T entityConvert = dynamic_cast<T>(TypeA))
	{
		return entityConvert;
	}
	return nullptr;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetAllTypeConvert(std::vector<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	int lenght = tabTypeA.size();
	for (int i = 0; i < lenght; ++i)
	{
		if (T* entityConvert = dynamic_cast<T*>(tabTypeA[i]))
		{
			allTypeT.push_back(entityConvert);
		}
	}
	return allTypeT;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetAllTypeConvert(std::list<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	for (auto it = (tabTypeA).begin(); it != (tabTypeA).end(); )
	{
		if (T* entityConvert = dynamic_cast<T*>(*it))
		{
			allTypeT.push_back(entityConvert);
		}
		++it;
	}
	return allTypeT;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetConvertVector(std::vector<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	for (int i = 0; i < (int)tabTypeA.size(); ++i)
	{
		allTypeT.push_back(tabTypeA[i]);
	}
	return allTypeT;
}

template<typename T>
inline bool Garden::VectorIsEmpty(std::vector<T*> tabTypeA)
{
	if ((int)tabTypeA.size() == 0)
	{
		return true;
	}
	return false;
}

template<typename T>
inline std::vector<T*> Garden::AllEntityInline(int line)
{
	std::vector<T*> allEntityInLine;
	std::vector<T*> allEntity = GetAllTypeConvert<T>(*mAllEntity);
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
