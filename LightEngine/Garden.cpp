#include "Garden.h"

#include "Zombie.h"
#include "Shot.h"
#include "Plant.h"

#include "Debug.h"

void Garden::OnInitialize()
{
	mAllEntity = GameManager::Get()->GetTabEntity();
	mModeCreator = MODEZOMBIE;

	CreatPlant(50, sf::Vector2f(COLLUMPLANT, LINEONE), false, 3);

	CreatPlant(50, sf::Vector2f(COLLUMPLANT, LINETWO), false, 3);

	CreatPlant(50, sf::Vector2f(COLLUMPLANT, LINETHREE), false, 3);

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

void Garden::CreatZombie(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	Zombie* zombie = CreateEntity<Zombie>(radius, sf::Color::White);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life);
	zombie->Init(0, speed, 0.f, 0.f, 0.f, WALKINGUSE, zombie);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color::Yellow);
}

void Garden::CreatPlant(float radius, sf::Vector2f pos, bool rigidBody, int life)
{
	Plant* plant = CreateEntity<Plant>(radius, sf::Color::White);
	plant->SetPosition(pos.x, pos.y);
	plant->SetRigidBody(rigidBody);
	plant->SetLife(life * 100);
	plant->Init(3, 0.f, 3.f, 1.f, 1.f, SHOOTINGUSE, plant);
	plant->SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::EventType::MouseButtonPressed)
	{
		OnEventMouse(event);
	}
	if (event.type != sf::Event::EventType::KeyPressed)
	{
		OnEventKeyboard(event);
	}
}

void Garden::OnEventMouse(const sf::Event& event)
{
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
			if (mModeCreator == MODEZOMBIE)
			{
				CreatZombie(50, sf::Vector2f(COLLUMZOMBIE, LINEONE), true, 3, 20.f);
			}
			else if (mModeCreator == MODEPLANT)
			{
				CreatNewPlant(50, LINEONE, true, 3);
			}
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Middle)
	{
		if (mModeCreator == MODEZOMBIE)
		{
			CreatZombie(50, sf::Vector2f(COLLUMZOMBIE, LINETWO), true, 3, 20.f);
		}
		else if (mModeCreator == MODEPLANT)
		{

		}
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
			if (mModeCreator == MODEZOMBIE)
			{
				CreatZombie(50, sf::Vector2f(COLLUMZOMBIE, LINETHREE), true, 3, 20.f);
			}
			else if (mModeCreator == MODEPLANT)
			{

			}
		}
	}
}

void Garden::OnEventKeyboard(const sf::Event& event)
{
	if (event.KeyPressed == sf::Keyboard::Space)
	{
		mModeCreator++;
		if (mModeCreator < MAXMODECREATOR)
		{
			return;
		}
		mModeCreator = 0;
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
	return IsLineEmptyEnemy(itMe->GetType(), itMe->GetPosition().y);
}

bool Garden::IsAlongLineUp(Entity* itMe)
{
	return IsLineEmptyEnemy(itMe->GetType(), itMe->GetPosition().y - HEIGHTLINE);
}

bool Garden::IsAlongLineDown(Entity* itMe)
{
	return IsLineEmptyEnemy(itMe->GetType(), itMe->GetPosition().y + HEIGHTLINE);
}

bool Garden::IsLineEmptyEnemy(int itMeType, float itMePos)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (IsEnemieInLine(itMePos, (*it)->GetPosition().y, itMeType, (*it)->GetType()))//(itMePos.y == (*it)->GetPosition().y)(itMe->GetType() != (*it)->GetType())
		{
			return false;
		}
		++it;
	}
	return true;
}

bool Garden::IsAreaEmpty(Entity* itMe, float area)
{
	return IsZoneEmptyEnemy(itMe->GetType(), itMe->GetPosition(), area);
}

bool Garden::IsAreaEmptyUp(Entity* itMe, float area)
{
	return IsZoneEmptyEnemy(itMe->GetType(), itMe->GetPosition() - sf::Vector2f(0, HEIGHTLINE), area);
}

bool Garden::IsAreaEmptyDown(Entity* itMe, float area)
{
	return IsZoneEmptyEnemy(itMe->GetType(), itMe->GetPosition() + sf::Vector2f(0,HEIGHTLINE), area);
}

bool Garden::IsZoneEmptyEnemy(int itMeType, sf::Vector2f itMePos, float area)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (IsEnemieInLine(itMePos.y, (*it)->GetPosition().y, itMeType, (*it)->GetType()))//(itMePos.y == (*it)->GetPosition().y)(itMe->GetType() != (*it)->GetType())
		{
			if(itMePos.x + area > (*it)->GetPosition().x && itMePos.x - area < (*it)->GetPosition().x)
			{
				return false;
			}
		}
		++it;
	}
	return true;
}

bool Garden::IsEnemieInLine(float itMePos, float entityPos, int itMeType, int entityType)
{
	if (itMePos == entityPos)
	{
		if (itMeType != entityType)
		{
			return true;
		}
	}
	return false;
}

bool Garden::IsAllieInLine(float itMePos, float entityPos, int itMeType, int entityType)
{
	if (itMePos == entityPos)
	{
		if (itMeType == entityType)
		{
			return true;
		}
	}
	return false;
}

bool Garden::IsEmptyPlantInLine(Entity* itMe)
{
	return IsLineEmptyPlant(itMe->GetPosition().y);
}

bool Garden::IsEmptyPlantInLineUp(Entity* itMe)
{
	return IsLineEmptyPlant(itMe->GetPosition().y - HEIGHTLINE);
}

bool Garden::IsEmptyPlantInLineDown(Entity* itMe)
{
	return IsLineEmptyPlant(itMe->GetPosition().y + HEIGHTLINE);
}

bool Garden::IsLineEmptyPlant(float itMePos)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (IsPlantInLine(itMePos, (*it)->GetPosition().y, *it))
		{
			return false;
		}
		++it;
	}
	return true;
}

bool Garden::IsPlantInLine(float itMePos, float entityPos, Entity* entity)
{
	if (itMePos == entityPos)
	{
		if (GetTypeConvert<Plant*>(entity))
		{
			return true;
		}
	}
	return false;
}

bool Garden::IsZoneEmptyPlant(sf::Vector2f itMePos, float area)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (IsPlantInLine(itMePos.y, (*it)->GetPosition().y, *it))//(itMePos.y == (*it)->GetPosition().y)(itMe->GetType() != (*it)->GetType())
		{
			if (itMePos.x + area > (*it)->GetPosition().x && itMePos.x - area < (*it)->GetPosition().x)
			{
				return false;
			}
		}
		++it;
	}
	return true;
}


void Garden::CreatNewPlant(float radius, int line, bool rigidBody, int life)
{
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{

	}
}
