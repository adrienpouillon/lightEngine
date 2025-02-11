#include "DummyEntity.h"

#include "SampleScene.h"

#include <iostream>

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
	float currenteRadius = mShape.getRadius();
	if (currenteRadius > 1)
	{
		mShape.setRadius(currenteRadius - 0.5f);
	}
	else
	{
		GetScene<SampleScene>()->CreatDummyEntity(2,sf::Color::Cyan, GetPosition(mShape.getRadius() + 3.f, mShape.getRadius() + 3.f),true);
	}
	
}

void DummyEntity::UpdateEntity()
{
	mShape.setRadius(mShape.getRadius() + 0.05f);
}
