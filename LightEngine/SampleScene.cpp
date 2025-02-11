#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	CreatDummyEntity(100, sf::Color::Red, sf::Vector2f(100,100), true);

	CreatDummyEntity(50, sf::Color::Green, sf::Vector2f(500, 500), true);

	CreatDummyEntity(75, sf::Color::Blue, sf::Vector2f(1000, 300), true);

	CreatDummyEntity(25, sf::Color::Magenta, sf::Vector2f(200, 700), true);

	pEntitySelected = nullptr;
}

void SampleScene::CreatDummyEntity(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody)
{
	mAllEntity.push_back(CreateEntity<DummyEntity>(radius, color));
	int index = (int)mAllEntity.size() - 1;
	mAllEntity[index]->SetPosition(pos.x, pos.y);
	mAllEntity[index]->SetRigidBody(true);
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		for (int i = 0; i < mAllEntity.size(); i++)
		{
			TrySetSelectedEntity(mAllEntity[i], event.mouseButton.x, event.mouseButton.y);
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	//for (int i = 0; i < mAllEntity.size(); i++)
	//{
	//	mAllEntity[i]->UpdateEntity();
	//}
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 3, sf::Color::Blue);
	}
}