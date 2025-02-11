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
		SampleScene* scene = GetScene<SampleScene>();
		DuplicateDummyEntity(mShape, scene);
		DuplicateDummyEntity(mShape, scene);
	}
}

void DummyEntity::OnUpdate()
{
	mShape.setRadius(mShape.getRadius() + 0.05f);
}

void  DummyEntity::DuplicateDummyEntity(sf::CircleShape shape, SampleScene* scene)
{
	sf::Color color = scene->ChooseColor(scene->GenerateRandomNumber(WHITE, BLACK));
	int radius = scene->GenerateRandomNumber(1, 5);
	float moreLessPos = (float)scene->GenerateRandomNumber(1, 5);
	scene->CreatDummyEntity(radius, color, GetPosition(shape.getRadius() + moreLessPos, shape.getRadius() + moreLessPos), true);
}
