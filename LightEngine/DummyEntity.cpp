#include "DummyEntity.h"

#include "SampleScene.h"

#include <iostream>
void DummyEntity::OnInitialize()
{
	mTimeDuplicate = 10.f;
	mDefence = 1.f;
}

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
	float currenteRadius = mShape.getRadius();
	if (currenteRadius > 1)
	{
		mShape.setRadius(currenteRadius - mDefence);
	}
	else
	{
		if (mTimeDuplicate < 0.f)
		{
			SampleScene* scene = GetScene<SampleScene>();
			if (mShape.getFillColor() != other->GetShape()->getFillColor())
			{
				
				DuplicateDummyEntity(mShape, scene);
				DuplicateDummyEntity(mShape, scene);
			}
			else
			{
				DummyEntity* dummyEntity = scene->GetTypeConvert<DummyEntity*>(other);
				dummyEntity->SetDefence(dummyEntity->GetDefence() - (0.05f / mDefence));
			}
			Destroy();
		}
	}
}

void DummyEntity::OnUpdate()
{
	mShape.setRadius(mShape.getRadius() + 0.05f);
	mTimeDuplicate -= GetDeltaTime();
}

void DummyEntity::DuplicateDummyEntity(sf::CircleShape shape, SampleScene* scene)
{
	sf::Color color = scene->ChooseColor(scene->GenerateRandomNumber(WHITE, BLACK));
	int radius = scene->GenerateRandomNumber(1, 5);
	float moreLessPos = (float)scene->GenerateRandomNumber(-30, 30);
	scene->CreatDummyEntity(radius, color, GetPosition(shape.getRadius() + moreLessPos, shape.getRadius() + moreLessPos), true);
}

void DummyEntity::SetDefence(float defence)
{
	mDefence = defence;
}

float DummyEntity::GetDefence()
{
	return mDefence;
}