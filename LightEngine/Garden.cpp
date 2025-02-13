#include "Garden.h"

#include "Zombie.h"
#include "Shot.h"
#include "Plant.h"

#include "Debug.h"

void Garden::OnInitialize()
{
	mAllEntity = GameManager::Get()->GetTabEntity();

	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINEONE), false, 3);

	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINETWO), false, 3);

	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINETHREE), false, 3);

}

void Garden::CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type, float verticalDirection)
{
	Shot* shot = CreateEntity<Shot>(radius, color);
	shot->SetPosition(pos.x, pos.y + verticalDirection);
	shot->SetRigidBody(rigidBody);
	shot->SetLife(life);
	shot->SetType(type);
	shot->SetDirectionShot(sf::Vector2f(pos.x, pos.y + verticalDirection*2));
}

void Garden::CreatZombie(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life)
{
	
	Zombie* zombie = CreateEntity<Zombie>(radius, color);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life);
	zombie->Init(0, 0.f, 0.f, 0.f, WALKINGUSE, zombie);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Magenta, sf::Color::Yellow);
}

void Garden::CreatPlant(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life)
{
	Plant* plant = CreateEntity<Plant>(radius, color);
	plant->SetPosition(pos.x, pos.y);
	plant->SetRigidBody(rigidBody);
	plant->SetLife(life * 100);
	plant->Init(3, 3.f, 1.f, 1.f, SHOOTINGUSE, plant);
	plant->SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		bool isExecute = false;
		for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
		{
			if (TryShot(*it, event.mouseButton.x, event.mouseButton.y))
			{
				isExecute = true;
			}
			++it;
		}

		if (!isExecute)
		{
			CreatZombie(50, sf::Color::Red, sf::Vector2f(COLLUMZOMBIE, LINEONE), true, 3);
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Middle)
	{
		CreatZombie(50, sf::Color::Red, sf::Vector2f(COLLUMZOMBIE, LINETWO), true, 3);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		bool isExecute = false;
		for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
		{
			if (TryShotRoc(*it, event.mouseButton.x, event.mouseButton.y))
			{
				isExecute = true;
			}
			++it;
		}

		if (!isExecute)
		{
			CreatZombie(50, sf::Color::Red, sf::Vector2f(COLLUMZOMBIE, LINETHREE), true, 3);
		}
	}
}

void Garden::OnUpdate()
{
	//for (int i = 0; i < mAllEntity.size(); i++)
	//{
	//	mAllEntity[i]->UpdateEntity();
	//}
}

bool Garden::TryShot(Entity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return false;
	InstanceShot(pEntity, 0.f);
	return true;
}

bool Garden::TryShotRoc(Entity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return false;
	InstanceShotRoc(pEntity, 0.f);
	return true;
}

void Garden::InstanceShot(Entity* itsCreator, float verticalDirection)
{
	int radiusShot = 25;
	sf::Vector2f pos = itsCreator->GetPosition();
	int sizeEntity = itsCreator->GetRadius();
	int type = itsCreator->GetType();
	if (type == TYPEZOMBIE)
	{
		sizeEntity = -(sizeEntity + radiusShot);
	}
	CreatShot(radiusShot, sf::Color::Yellow, sf::Vector2f(pos.x + sizeEntity, pos.y), false, 1, type, verticalDirection);
}

void Garden::InstanceShotRoc(Entity* itsCreator, float verticalDirection)
{
	int radiusShot = 25;
	sf::Vector2f pos = itsCreator->GetPosition();
	int sizeEntity = itsCreator->GetRadius();
	int type = itsCreator->GetType();
	if (type == TYPEZOMBIE)
	{
		sizeEntity = -(sizeEntity + radiusShot);
	}
	CreatShot(radiusShot, sf::Color::Magenta, sf::Vector2f(pos.x + sizeEntity, pos.y), false, 1*20, type, verticalDirection);
}

bool Garden::IsAlongLine(Entity* itMe)
{
	return IsLineEmpty(itMe, itMe->GetPosition().y);
}

bool Garden::IsAlongLineUp(Entity* itMe)
{
	return IsLineEmpty(itMe, itMe->GetPosition().y - HEIGHTLINE);
}

bool Garden::IsAlongLineDown(Entity* itMe)
{
	return IsLineEmpty(itMe, itMe->GetPosition().y + HEIGHTLINE);
}

bool Garden::IsLineEmpty(Entity* itMe, float itMePos)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (itMePos == (*it)->GetPosition().y)
		{
			if (itMe->GetType() != (*it)->GetType())
			{
				return false;
			}
		}
		++it;
	}
	return true;
}
