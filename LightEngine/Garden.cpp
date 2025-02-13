#include "Garden.h"

#include "Zombie.h"
#include "Shot.h"
#include "Plant.h"

#include "Debug.h"

void Garden::OnInitialize()
{
	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINEONE), false, 3);

	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINETWO), false, 3);

	CreatPlant(50, sf::Color::Green, sf::Vector2f(COLLUMPLANT, LINETHREE), false, 3);

}

void Garden::CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type)
{
	mAllEntity.push_back(CreateEntity<Shot>(radius, color));
	int index = (int)mAllEntity.size() - 1;
	
	Shot* shot = GetTypeConvert<Shot*>(mAllEntity[index]);
	shot->SetPosition(pos.x, pos.y);
	shot->SetRigidBody(rigidBody);
	shot->SetLife(life);
	shot->SetType(type);
}

void Garden::CreatZombie(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life)
{
	mAllEntity.push_back(CreateEntity<Zombie>(radius, color));
	int index = (int)mAllEntity.size() - 1;
	
	Zombie* zombie = GetTypeConvert<Zombie*>(mAllEntity[index]);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life);
	zombie->Init(0, 0, 0, WALKINGUSE, zombie);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color::Yellow);
}

void Garden::CreatPlant(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life)
{
	mAllEntity.push_back(CreateEntity<Plant>(radius, color));
	int index = (int)mAllEntity.size() - 1;

	Plant* plant = GetTypeConvert<Plant*>(mAllEntity[index]);
	plant->SetPosition(pos.x, pos.y);
	plant->SetRigidBody(rigidBody);
	plant->SetLife(life * 100);
	plant->Init(3, 3, 1, SHOOTINGUSE, plant);
	plant->SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		bool isExecute = false;
		for (int i = 0; i < mAllEntity.size(); i++)
		{
			if (TryShot(mAllEntity[i], event.mouseButton.x, event.mouseButton.y))
			{
				isExecute = true;
			}
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
		CreatZombie(50, sf::Color::Red, sf::Vector2f(COLLUMZOMBIE, LINETHREE), true, 3);
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
	InstanceShot(pEntity);
	return true;
}

void Garden::InstanceShot(Entity* itsCreator)
{
	int radiusShot = 25;
	sf::Vector2f pos = itsCreator->GetPosition();
	int sizeEntity = itsCreator->GetRadius();
	int type = itsCreator->GetType();
	if (type == TYPEZOMBIE)
	{
		sizeEntity = -(sizeEntity + radiusShot);
	}
	CreatShot(radiusShot, sf::Color::Yellow, sf::Vector2f(pos.x + sizeEntity, pos.y), false, 1, type);
}