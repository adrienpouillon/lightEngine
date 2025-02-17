#pragma once
#include "Entity.h"

class SampleScene;

class DummyEntity : public Entity
{
protected:
	float mTimeDuplicate;
	float mDefence;
public:
	void OnInitialize();

	void OnCollision(Entity* other) override;

	virtual void OnUpdate();

	void DuplicateDummyEntity(sf::CircleShape shape, SampleScene* scene);

	void SetDefence(float defence);

	float GetDefence();

};

