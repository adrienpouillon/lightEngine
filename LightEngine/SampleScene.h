#pragma once

#include "Scene.h"

class DummyEntity;

class SampleScene : public Scene
{
	std::vector<DummyEntity*> mAllEntity;

	DummyEntity* pEntitySelected;

	float mTimeBackGround;
	float mTimeBackGroundProgress;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;

	void CreatDummyEntity(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody);

	void OnEvent(const sf::Event& event) override;

	void OnUpdate() override;

	template<typename T, typename A>
	T GetTypeConvert(A TypeA);

	template<typename T, typename A>
	std::vector<T*> GetAllTypeConvert(std::vector<A*> tabTypeA);

	template<typename T, typename A>
	std::vector<T*> GetAllTypeConvert(std::list<A*> tabTypeA);
	
};

template<typename T, typename A>
inline T SampleScene::GetTypeConvert(A TypeA)
{
	if (T entityConvert = dynamic_cast<T>(TypeA))
	{
		return entityConvert;
	}
	return nullptr;
}

template<typename T, typename A>
inline std::vector<T*> SampleScene::GetAllTypeConvert(std::vector<A*> tabTypeA)
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
inline std::vector<T*> SampleScene::GetAllTypeConvert(std::list<A*> tabTypeA)
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