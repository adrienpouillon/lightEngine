#pragma once
#include "Entity.h"

class SampleScene;

class DummyEntity : public Entity
{
public:
	void OnCollision(Entity* other) override;

	virtual void OnUpdate();

	void DuplicateDummyEntity(sf::CircleShape shape, SampleScene* scene);

};

