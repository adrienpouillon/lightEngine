#pragma once

#include "Scene.h"

class DummyEntity;

class SampleScene : public Scene
{
	std::vector<DummyEntity*> mAllEntity;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;

	void CreatDummyEntity(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody);

	void OnEvent(const sf::Event& event) override;

	void OnUpdate() override;
	
};
