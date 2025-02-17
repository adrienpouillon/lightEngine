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
public:
	void OnInitialize();

	void CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type, float verticalDirection);

	void CreatZombie(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);

	void CreatPlant(float radius, sf::Vector2f pos, bool rigidBody, int life);

	void OnEvent(const sf::Event& event);

	void OnEventMouse(const sf::Event& event);

	void OnEventKeyboard(const sf::Event& event);

	void OnUpdate();

	bool TryShot(Entity* pEntity, float x, float y);

	bool TryShotRoc(Entity* pEntity, float x, float y);

	void InstanceShot(Entity* itsCreator, float verticalDirection);

	void InstanceShotRoc(Entity* itsCreator, float verticalDirection);

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

	void CreatNewPlant(float radius, bool rigidBody, int life, int line);

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
	for (int i = 0; i < tabTypeA.size(); ++i)
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
	for (auto it = (*tabTypeA).begin(); it != (*tabTypeA).end(); )
	{
		if (T* entityConvert = dynamic_cast<T*>(*it))
		{
			allTypeT.push_back(entityConvert);
		}
		++it;
	}
	return allTypeT;
}

