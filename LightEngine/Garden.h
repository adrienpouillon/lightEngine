#pragma once
#include "Scene.h"


#define COLLUMPLANT 100
#define COLLUMZOMBIE 1200
#define LINEONE 100
#define LINETWO 350
#define LINETHREE 600

class Garden :public Scene
{
protected:
	std::vector<Entity*> mAllEntity;
public:
	void OnInitialize();

	void CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type);

	void CreatZombie(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life);

	void CreatPlant(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life);

	void OnEvent(const sf::Event& event);

	void OnUpdate();

	bool TryShot(Entity* pEntity, int x, int y);

	template<typename T>
	T* GetEntity();

	template<typename T>
	std::vector<T*> GetAllEntity();

	template<typename T, typename A>
	T GetTypeConvert(A TypeA);

	template<typename T, typename A>
	std::vector<T*> GetAllTypeConvert(std::vector<A*> tabTypeA);

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
	for (int i = 0; i < mAllEntity.size(); ++i)
	{
		if (T* entity = dynamic_cast<T*>(mAllEntity[i]))
		{
			allT.push_back(entity);
		}
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

