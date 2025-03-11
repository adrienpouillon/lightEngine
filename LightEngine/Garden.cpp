#include "Garden.h"
#include "Utils.h"

#include "Shot.h"
#include "Sun.h"
#include "Zombie.h"
#include "ZombieRa.h"
#include "ZombieShot.h"
#include "Peat.h"
#include "Torch.h"
#include "SunFlower.h"
#include "Mower.h"
#include "Saw.h"
#include "Debug.h"

void Garden::OnInitialize()
{
	mAllEntity = GameManager::Get()->GetTabEntity();
	mModeCreator = MODEZOMBIE;
	mIaZombie = false;
	mIaPlant = true;
	mIaPlantCreat = false;
	mCheat = false;

	mDifficulty = CREATEMICRO;
	mTimeZombieCreatProgress = 25.f + (float)mDifficulty * 5.f;
	mNbCreationZombie = 0;
	mWave = -1;
	mHaveZombieInGame = false;

	mPlantCoin = 350;
	mZombieCoin = 1000;
	mZombiePass = 0;
	mZombieDestroy = 0;


	mMouse = CreateEntity<Mouse>(5, sf::Color::Red);

	srand(NULL);

}

void Garden::CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type, float verticalDirection)
{
	Shot* shot = CreateEntity<Shot>(radius, color);
	shot->SetPosition(pos.x, pos.y + verticalDirection);
	shot->SetRigidBody(rigidBody);
	shot->SetLife(life);
	shot->SetTag(type);
	shot->SetDirectionShot(sf::Vector2f(pos.x, pos.y + verticalDirection*2));
}

void Garden::CreatSun(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int type)
{
	Sun* sun = CreateEntity<Sun>(radius, color);
	sun->SetPosition(pos.x, pos.y);
	sun->SetRigidBody(rigidBody);
	sun->SetTag(type);
	sun->SetFallSun();
}

void Garden::CreatSun(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int type, sf::Vector2f nextPos, float speed)
{
	Sun* sun = CreateEntity<Sun>(radius, color);
	sun->SetPosition(pos.x, pos.y);
	sun->SetRigidBody(rigidBody);
	sun->SetTag(type);
	sun->GoToPosition(nextPos.x, nextPos.y, speed);
}

void Garden::CreatZombie(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	Zombie* zombie = CreateEntity<Zombie>(radius, sf::Color::Red);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life);
	zombie->Init(0, speed, 0.f, 0.f, 0.f, 0.f, WALKINGUSE, StateManager::State::Walking);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color::Yellow);
}

void Garden::CreatZombieCone(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	Zombie* zombie = CreateEntity<Zombie>(radius, sf::Color::Red);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life * 5);
	zombie->Init(0, speed/2, 0.f, 0.f, 0.f, 0.f, WALKINGUSE, StateManager::State::Walking);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Magenta, sf::Color::Yellow);
}

void Garden::CreatZombieSport(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	Zombie* zombie = CreateEntity<Zombie>(radius, sf::Color::Red);
	zombie->SetPosition(pos.x, pos.y);
	zombie->SetRigidBody(rigidBody);
	zombie->SetLife(life/4.f);
	zombie->Init(0, speed * 4.f, 0.f, 0.f, 0.f, 0.f, WALKINGUSE, StateManager::State::Walking);
	zombie->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Yellow);
}

void Garden::CreatZombieRa(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	ZombieRa* zombieRa = CreateEntity<ZombieRa>(radius, sf::Color::Red);
	zombieRa->SetPosition(pos.x, pos.y);
	zombieRa->SetRigidBody(rigidBody);
	zombieRa->SetLife(life);
	zombieRa->Init(0, speed, 0.f, 0.f, 0.f, 0.f, WALKINGUSE, StateManager::State::Walking);
	zombieRa->SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Yellow);
}

void Garden::CreatZombieShot(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed)
{
	ZombieShot* zombieShot = CreateEntity<ZombieShot>(radius, sf::Color::Red);
	zombieShot->SetPosition(pos.x, pos.y);
	zombieShot->SetRigidBody(rigidBody);
	zombieShot->SetLife(life);
	zombieShot->Init(1, speed / 2.f, 3.f, 1.f, 1.f, 4.f,  SHOOTINGWALKINGUSE, StateManager::State::Walking);
	zombieShot->SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Green, sf::Color::Yellow);
}

void Garden::CreatPeat(float radius, sf::Vector2f pos, bool rigidBody, int life)
{
	Peat* peat = CreateEntity<Peat>(radius, sf::Color::Green);
	peat->SetPosition(pos.x, pos.y);
	peat->SetRigidBody(rigidBody);
	peat->SetLife(life * 100);
	peat->Init(3, 0.f, 3.f, 1.f, 1.f, 0.f, SHOOTINGUSE, StateManager::State::Full);
	peat->SetAllColor(sf::Color::Green, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::CreatTorch(float radius, sf::Vector2f pos, bool rigidBody, int life)
{
	Torch* torch = CreateEntity<Torch>(radius, sf::Color::Red);
	torch->SetPosition(pos.x, pos.y);
	torch->SetRigidBody(rigidBody);
	torch->SetLife(life * 50);
	torch->Init(1, 0.f, 0.75f, 0.25f, 0.12f, 0.f, SHOOTINGUSE, StateManager::State::Full);
	torch->SetAllColor(sf::Color::Red, sf::Color::Red, sf::Color::White, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::CreatSunFlower(float radius, sf::Vector2f pos, bool rigidBody, int life)
{
	SunFlower* sunFlower = CreateEntity<SunFlower>(radius, sf::Color::Yellow);
	sunFlower->SetPosition(pos.x, pos.y);
	sunFlower->SetRigidBody(rigidBody);
	sunFlower->SetLife(life * 50);
	sunFlower->Init(2, 0.f, 5.f, 1.f, 2.f, 0.f, SHOOTINGUSE, StateManager::State::Empty);
	sunFlower->SetAllColor(sf::Color::Yellow, sf::Color::Yellow, sf::Color::Red, sf::Color::White, sf::Color::Cyan, sf::Color::White, sf::Color::White);
}

void Garden::CreatMower(float radius, sf::Vector2f pos, bool rigidBody)
{
	Mower* mower = CreateEntity<Mower>(radius, sf::Color::Magenta);
	mower->SetPosition(pos.x, pos.y);
	mower->SetRigidBody(rigidBody);
}

void Garden::CreatSaw(float radius, sf::Vector2f pos, bool rigidBody, int life)
{
	Saw* saw  = CreateEntity<Saw>(radius, sf::Color::White);
	saw->SetPosition(pos.x, pos.y);
	saw->SetRigidBody(rigidBody);
	saw->SetLife(life * 50);
}

void Garden::OnEvent(const sf::Event& event)
{
	if (event.mouseMove.x > 0 && event.mouseMove.y > 0)
	{
		SetMousePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
	}

	if (event.type == sf::Event::EventType::MouseButtonPressed)
	{
		OnEventMouse(event);
	}
	if (event.type == sf::Event::EventType::KeyPressed)
	{
		OnEventKeyboard(event);
		srand(NULL);
	}
}

void Garden::OnEventMouse(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if(mIaPlant)
		{
			for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
			{
				TryShot(*it, (float)event.mouseButton.x, (float)event.mouseButton.y);
				++it;
			}
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Middle)
	{
		for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
		{
			TryToErase(*it, (float)event.mouseButton.x, (float)event.mouseButton.y);
			++it;
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
		{
			TryShotRoc(*it, (float)event.mouseButton.x, (float)event.mouseButton.y);
			++it;
		}
	}
}

void Garden::OnEventKeyboard(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Space)
	{
		SetModeCreator(mModeCreator + 1);
		if (mModeCreator < MAXMODECREATOR)
		{
			return;
		}
		SetModeCreator(0);
	}

	if (event.key.code == sf::Keyboard::Z)
	{
		mIaZombie = !mIaZombie;
	}

	if (event.key.code == sf::Keyboard::P)
	{
		mIaPlant = !mIaPlant;
	}

	if (event.key.code == sf::Keyboard::M)
	{
		mIaPlantCreat = !mIaPlantCreat;
	}

	if (event.key.code == sf::Keyboard::C)
	{
		mCheat = !mCheat;
	}

	if (event.key.code == sf::Keyboard::D)
	{
		mDifficulty++;
	}

	if (event.key.code == sf::Keyboard::S)
	{
		if (mModeCreator == MODEZOMBIE)
		{
			mZombieCoin += 50;
		}
		else if(mModeCreator == MODEPLANT)
		{
			mPlantCoin += 50;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad0)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch(CreatPlantOrZombie(COSTZOMBIENORMAL, COSTPLANTPEAT))
		{
		case 1:
			//zombie creat + cost
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIENORMAL + 1));
			break;
		case 2:
			//zombie creat
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			break;

		case 3:
			//Plant creat + cost
			CreatNewPeat(ENTITYRADIUS, false, LIFEPLANT, line);
			IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			break;
		case 4:
			//zombie creat
			CreatNewPeat(ENTITYRADIUS, false, LIFEPLANT, line);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad1)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIECONE, COSTPLANTTORCH))
		{
		case 1:
			//zombie creat + cost
			CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIECONE, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIECONE + 1));
			break;
		case 2:
			//zombie creat
			CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIECONE, SPEEDZOMBIE);
			break;

		case 3:
			//Plant creat + cost
			CreatNewTorch(ENTITYRADIUS, false, LIFEPLANT, line);
			IncreasePlantCoin(-(COSTPLANTTORCH + 1));
			break;
		case 4:
			//zombie creat
			CreatNewTorch(ENTITYRADIUS, false, LIFEPLANT, line);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad2)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIESPORT, COSTPLANTSUNFLOWER))
		{
		case 1:
			//zombie creat + cost
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIESPORT, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIESPORT + 1));
			break;
		case 2:
			//zombie creat
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIESPORT, SPEEDZOMBIE);
			break;

		case 3:
			//Plant creat + cost
			CreatNewSunFlower(ENTITYRADIUS, false, LIFEPLANT, line);
			IncreasePlantCoin(-(COSTPLANTSUNFLOWER + 1));
			break;
		case 4:
			//zombie creat
			CreatNewSunFlower(ENTITYRADIUS, false, LIFEPLANT, line);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad3)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIERA, COSTPLANTSAW))
		{
		case 1:
			//zombie creat + cost
			CreatZombieRa(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIERA, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIERA + 1));
			break;
		case 2:
			//zombie creat
			CreatZombieRa(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIERA, SPEEDZOMBIE);
			break;

		case 3:
			//Plant creat + cost
			CreatNewSaw(ENTITYRADIUS, false, LIFEPLANT, mMousePos.x);
			IncreasePlantCoin(-(COSTPLANTSAW + 1));
			break;
		case 4:
			//zombie creat
			CreatNewSaw(ENTITYRADIUS, false, LIFEPLANT, mMousePos.x);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad4)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIESHOT, COSTPLANTMOWER))
		{
		case 1:
			//zombie creat + cost
			CreatZombieShot(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIESHOT, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIESHOT + 1));
			break;
		case 2:
			//zombie creat
			CreatZombieShot(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIESHOT, SPEEDZOMBIE);
			break;

		case 3:
			//Plant creat + cost
			CreatNewMower(ENTITYRADIUS, false, line);
			IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			break;
		case 4:
			//zombie creat
			CreatNewMower(ENTITYRADIUS, false, line);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad5)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIEBIG, 0))
		{
		case 1:
			//zombie creat + cost
			CreatZombie(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE * 20, SPEEDZOMBIE);
			IncreaseZombieCoin(-(COSTZOMBIECONEBIG + 1));
			break;
		case 2:
			//zombie creat
			CreatZombie(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE * 20, SPEEDZOMBIE);
			break;
		case 3:
			//Plant creat + cost
			//CreatNewMower(ENTITYRADIUS, false, line);
			//IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			break;
		case 4:
			//zombie creat
			//CreatNewMower(ENTITYRADIUS, false, line);
			break;
		}
	}

	if (event.key.code == sf::Keyboard::Numpad6)
	{
		int line = LineUtils::SeachLine(mMousePos.y);
		switch (CreatPlantOrZombie(COSTZOMBIECONEBIG, 0))
		{
		case 1:
			//zombie creat + cost
			CreatZombieCone(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE * 10, SPEEDZOMBIE / 2);
			IncreaseZombieCoin(-(COSTZOMBIECONEBIG + 1));
			break;
		case 2:
			//zombie creat
			CreatZombieCone(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE, line), true, LIFEZOMBIE * 10, SPEEDZOMBIE / 2);
			break;
		case 3:
			//Plant creat + cost
			//CreatNewMower(ENTITYRADIUS, false, line);
			//IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			break;
		case 4:
			//zombie creat
			//CreatNewMower(ENTITYRADIUS, false, line);
			break;
		}
	}
}

int Garden::CreatPlantOrZombie(int costZombie, int costPlant)
{
	if (!mCheat)
	{
		if (mModeCreator == MODEZOMBIE)
		{
			if (mZombieCoin > costZombie)
			{
				return 1;
			}
		}
		else if (mModeCreator == MODEPLANT)
		{
			if (mPlantCoin > costPlant)
			{
				return 3;
			}
		}
	}
	else
	{
		if (mModeCreator == MODEZOMBIE)
		{
			return 2;
		}
		else if (mModeCreator == MODEPLANT)
		{
			return 4;
		}
	}
	return 0;
}

void Garden::OnUpdate()
{
	if(mIaZombie)
	{
		IaActionZombie();
	}
	if (mIaPlantCreat)
	{
		IaActionPlantCreat();
	}

	if (mModeCreator == MODEZOMBIE)
	{
		DrawZombie();
	}
	else
	{
		DrawPlant();
	}

	FallSun(300);

	CountWave();
}

void Garden::DrawPlant()
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	sf::Color colorCoin;
	if (!mCheat)
	{
		if (mIaPlantCreat)
		{
			colorCoin = sf::Color::Blue;
		}
		else
		{
			colorCoin = sf::Color::Green;
		}
	}
	else
	{
		colorCoin = sf::Color::White;
	}

	std::string stringCoin = std::to_string(mPlantCoin) + " Soleil";
	Debug::DrawText(((float)sizeWindow.x / 16.f), 0.f, stringCoin, colorCoin);

	std::string stringDestroy = std::to_string(mZombieDestroy) + " Zombie tue'";
	Debug::DrawText((float)(sizeWindow.x * 5) / 8.f, 0.f, stringDestroy, sf::Color::Green);

	std::string stringZombieCreat;
	if (mIaZombie)
	{
		if (CREATEMICRO > mDifficulty) { stringZombieCreat = "Mode: Dormant"; }
		else if (CREATELOW > mDifficulty) { stringZombieCreat = "Mode: Tres Lent"; }
		else if (CREATENORMAL > mDifficulty) { stringZombieCreat = "Mode: Lent"; }
		else if (CREATEFAST > mDifficulty) { stringZombieCreat = "Mode: Normal"; }
		else if (CREATEAPPOCALYPSE > mDifficulty) { stringZombieCreat = "Mode: Rapide"; }
		else if (CREATEINFINITY > mDifficulty) { stringZombieCreat = "Mode: Appocalypse"; }
		else if (CREATENOSTOP > mDifficulty) { stringZombieCreat = "Mode: Infinity"; }
		else if (mDifficulty > CREATENOSTOP) { stringZombieCreat = "Mode: Non Stop"; }
		else { stringZombieCreat = "Mode: Aucun"; }
	}
	else
	{
		stringZombieCreat = "Mode: Aucun";
	}
	Debug::DrawText((float)(sizeWindow.x * 5) / 6.f, 0.f, stringZombieCreat, sf::Color::Red);
}

void Garden::DrawZombie()
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	sf::Color colorCoin;
	if (!mCheat)
	{
		colorCoin = sf::Color::Red;
	}
	else
	{
		colorCoin = sf::Color::White;
	}

	std::string stringCoin = std::to_string(mZombieCoin) + " Cerveaux ";
	Debug::DrawText(((float)sizeWindow.x / 16.f), 0.f, stringCoin, colorCoin);

	std::string stringPass = std::to_string(mZombiePass) + " Zombie qui a passe' vos defenses";
	Debug::DrawText(((float)sizeWindow.x / 4.f), 0.f, stringPass, sf::Color::Red);

	std::string stringEat = std::to_string(mPlantEated) + " Plante manger";
	Debug::DrawText((float)(sizeWindow.x * 5) / 8.f, 0.f, stringEat, sf::Color::Red);

	std::string stringWave = std::to_string(mWave) + " Wave Lose";
	Debug::DrawText((float)(sizeWindow.x * 5) / 6.f, 0.f, stringWave, sf::Color::Green);
}

void Garden::FallSun(int probability)
{
	sf::Vector2i size = GameManager::Get()->GetWindowSize();
	sf::Vector2f min = sf::Vector2f(ENTITYRADIUS, (float)-size.y + ENTITYRADIUS);
	sf::Vector2f max = sf::Vector2f((float)size.x - ENTITYRADIUS, -ENTITYRADIUS);
	if (Garden::GenerateRandomNumber(0, probability) == 0)
	{
		sf::Vector2f ran = MoreLess(min, max);
		InstanceSun(sf::Vector2f(ran.x, ran.y));
	}
}

bool Garden::TryToErase(Entity* pEntity, float x, float y)
{
	if (pEntity == mMouse)
		return false;
	if (pEntity->IsInside(x, y) == false)
		return false;

	if (Plant* plant = GetTypeConvert<Plant*>(pEntity))
	{
		plant->Destroy();
		IncreasePlantCoin(50);
		return true;
	}
	return false;
}

bool Garden::TryCollect(Entity* pEntity, float x, float y)
{
	if (pEntity == mMouse)
		return false;
	if (pEntity->IsInside(x, y) == false)
		return false;

	if (Sun* sun = GetTypeConvert<Sun*>(pEntity))
	{
		sun->ActionDead();
		return true;
	}
	return false;
}

bool Garden::TryShot(Entity* pEntity, float x, float y)
{
	if (pEntity == mMouse)
		return false;
	if (pEntity->IsInside(x, y) == false)
		return false;

	if(mIaPlant == false)
	{
		if (Plant* plant = GetTypeConvert<Plant*>(pEntity))
		{
			if (plant->GetCanShoot()) {/*on peut tirer*/plant->Shoot(TAGACTION1); }
			else if (plant->GetCanReload()) {/*si peut super charger*/plant->Reload(); }
			return true;
		}
	}

	InstanceShot(pEntity, 0.f);
	return true;
}

bool Garden::TryShotRoc(Entity* pEntity, float x, float y)
{
	if (pEntity == mMouse)
		return false;
	if (pEntity->IsInside(x, y) == false)
		return false;

	if (mIaPlant == false)
	{
		if (Plant* plant = GetTypeConvert<Plant*>(pEntity))
		{
			if (plant->GetCanShoot()) {/*on peut tirer*/plant->Shoot(TAGACTION2); }
			else if (plant->GetCanReload()) {/*si peut super charger*/plant->Reload(); }
			return true;
		}
	}

	InstanceShotRoc(pEntity, 0.f);
	return true;
}

void Garden::InstanceShot(Entity* itsCreator, float verticalDirection, sf::Vector2f pos, float radiusShot)
{
	float sizeEntity = itsCreator->GetRadius();
	int type = itsCreator->GetTag();
	if (type <= TYPEZOMBIE)
	{
		sizeEntity = -(sizeEntity + radiusShot);
	}
	CreatShot(radiusShot, sf::Color::Yellow, sf::Vector2f(pos.x + sizeEntity, pos.y), false, 1, type, verticalDirection);
}

void Garden::InstanceShotRoc(Entity* itsCreator, float verticalDirection, sf::Vector2f pos, float radiusShot)
{
	float sizeEntity = itsCreator->GetRadius();
	int type = itsCreator->GetTag();
	if (type <= TYPEZOMBIE)
	{
		sizeEntity = -(sizeEntity + radiusShot);
	}
	CreatShot(radiusShot, sf::Color::Magenta, sf::Vector2f(pos.x + sizeEntity, pos.y), false, 1 * 20, type, verticalDirection);
}

void Garden::CountWave()
{
	if (mHaveZombieInGame == true)
	{
		if (EUtils::NbEntityInLine<Zombie>(LINEONE))
			return;
		if (EUtils::NbEntityInLine<Zombie>(LINETWO))
			return;
		if (EUtils::NbEntityInLine<Zombie>(LINETHREE))
			return;
		mHaveZombieInGame = false;
	}
	else
	{
		if (EUtils::NbEntityInLine<Zombie>(LINEONE) || EUtils::NbEntityInLine<Zombie>(LINETWO) || EUtils::NbEntityInLine<Zombie>(LINETHREE) && mDifficulty != mFormerDifficulty)
		{
			mHaveZombieInGame = true;
			mWave++;
			mFormerDifficulty = mDifficulty;
		}
	}
}

void Garden::CreatNewPeat(float radius, bool rigidBody, int life, int line)
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	for (int i = STARTAREACREATPLANT;  i < ENDAREACREATPLANT; i += BETEWEENPLANT)
	{
		if (EUtils::IsZoneEmptyEntity<Plant>(sf::Vector2f((float)i,(float)line), 100.f))
		{
			CreatPeat(radius, sf::Vector2f((float)i, (float)line), rigidBody, life);
			break;
		}
	}
}

void Garden::CreatNewTorch(float radius, bool rigidBody, int life, int line)
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	for (int i = STARTAREACREATPLANT; i < ENDAREACREATPLANT; i += BETEWEENPLANT)
	{
		if (EUtils::IsZoneEmptyEntity<Plant>(sf::Vector2f((float)i, (float)line), 100.f))
		{
			CreatTorch(radius, sf::Vector2f((float)i, (float)line), rigidBody, life);
			break;
		}
	}
}

void Garden::CreatNewSunFlower(float radius, bool rigidBody, int life, int line)
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	for (int i = STARTAREACREATPLANT; i < ENDAREACREATSAW; i += BETEWEENPLANT)
	{
		if (EUtils::IsZoneEmptyEntity<Plant>(sf::Vector2f((float)i, (float)line), 100.f))
		{
			CreatSunFlower(radius, sf::Vector2f((float)i, (float)line), rigidBody, life);
			break;
		}
	}
}

void Garden::CreatNewMower(float radius, bool rigidBody, int line)
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	for (int i = STARTAREACREATMOWER; i < STARTAREACREATPLANT; i += BETEWEENPLANT)
	{
		if (EUtils::IsZoneEmptyEntity<Plant>(sf::Vector2f((float)i, (float)line), 100.f))
		{
			CreatMower(radius, sf::Vector2f((float)i, (float)line), rigidBody);
			break;
		}
	}
}

void Garden::CreatNewSaw(float radius, bool rigidBody, int life, int posX)
{
	sf::Vector2i sizeWindow = GameManager::Get()->GetWindowSize();
	for (int i = STARTAREACREATSAW; i < ENDAREACREATSAW; i += BETEWEENPLANT)
	{
		if (i - (BETEWEENPLANT/2) < posX && posX < i + (BETEWEENPLANT / 2))
		{ 
			if (EUtils::IsCollumEmptyEntity<Saw>((float)i))
			{
				CreatSaw(radius, sf::Vector2f((float)i, (float)LINETWO), rigidBody, life);
				break;
			}
		}
	}
}

void Garden::IaActionPlantCreat()
{
	if (mPlantCoin < COSTPLANTMINI)
		return;

	//on peut crée la plante qui cout la moins cher 
	int line = LineUtils::LineLessEntityAndMoreEmpty(EUtils::NbEntityInLine<Plant>(LINEONE), EUtils::NbEntityInLine<Plant>(LINETWO), EUtils::NbEntityInLine<Plant>(LINETHREE), EUtils::NbEntityInLine<Zombie>(LINEONE), EUtils::NbEntityInLine<Zombie>(LINETWO), EUtils::NbEntityInLine<Zombie>(LINETHREE));
	if (line == -1)
	{/*line invalide*/line = LineUtils::RandomLine(NBLINE, LINEONE, HEIGHTLINE);}
	/*int lineEntity = LineUtils::LineLessEntity(EUtils::NbEntityInLine<Plant>(LINEONE), EUtils::NbEntityInLine<Plant>(LINETWO), EUtils::NbEntityInLine<Plant>(LINETHREE));
	int lineEmpty = LineUtils::LineMoreEmpty(EUtils::NbEntityInLine<Zombie>(LINEONE), EUtils::NbEntityInLine<Zombie>(LINETWO), EUtils::NbEntityInLine<Zombie>(LINETHREE));
	if (lineEntity == -1)
	{
		//line Entity invalide
		if (lineEmpty == -1)
		{
			//line Entity et Empty invalide
			line = LineUtils::RandomLine(NBLINE, LINEONE, HEIGHTLINE);
		}
		else
		{
			//line Empty valide
			line = lineEmpty;
		}
	}
	else if (lineEmpty == -1)
	{
		//line Entity valide
		line = lineEntity;
	}
	else
	{
		//line Entity et Empty valide
		line = lineEntity;
	}*/

	int nbPlant = EUtils::NbEntityInLine<Plant>(line);
	if (nbPlant == NBPLANT)
		return;

	//la line a moins du maximun de plante
	if (mPlantCoin > COSTPLANTSUNFLOWER)
	{
		if (nbPlant == 0)
		{
			//si pas de plante et ennemie cree une mower
			if (!EUtils::IsLineEmptyEnemy(TYPEPLANT, line))
			{
				if(VectorIsEmpty(MUtils::AllMowerInline(line)))
				{
					IACreatMower(line);
					return;
				}
			}
		}

		if (nbPlant > 5)
		{
			//si beaucoup plante et pas beaucoup de sunflower déraciner une plante et cree un sunflower
			bool erase = false;
			std::vector<Plant*> allPlant = EUtils::AllEntityInline<Plant>(line);
			int lenght = allPlant.size();
			for (int i = 0; i < lenght; ++i)
			{
				sf::Vector2f pos = allPlant[i]->GetPosition();
				if (pos.x == STARTAREACREATPLANT)
				{
					if (GetTypeConvert<SunFlower*>(allPlant[i]) == nullptr)
					{
						if (TryToErase(allPlant[i], STARTAREACREATPLANT, line));
						{
							CreatNewSunFlower(ENTITYRADIUS, false, LIFEPLANT, line);
							IncreasePlantCoin(-(COSTPLANTSUNFLOWER + 1));
							erase = true;
							break;
						}
					}
				}
				else if(pos.x == STARTAREACREATPLANT + BETEWEENPLANT)
				{
					if (GetTypeConvert<SunFlower*>(allPlant[i]) == nullptr)
					{
						TryToErase(allPlant[i], STARTAREACREATPLANT, line);
						CreatNewSunFlower(ENTITYRADIUS, false, LIFEPLANT, line);
						IncreasePlantCoin(-(COSTPLANTSUNFLOWER + 1));
						erase = true;
						break;
					}
				}
			}

			if (!erase)
			{
				IACreatPeatTorch(nbPlant, line);
			}
			return;
		}

		//sinon creer une plante en fonction du nombre
		if (nbPlant < GenerateRandomNumber(1, 3))
		{
			CreatNewSunFlower(ENTITYRADIUS, false, LIFEPLANT, line);
			IncreasePlantCoin(-(COSTPLANTSUNFLOWER + 1));
			return;
		}
		else if (nbPlant < GenerateRandomNumber(4, 5))
		{
			CreatNewPeat(ENTITYRADIUS, false, LIFEPLANT, line);
			IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			return;
		}
		else if (nbPlant > 7)
		{
			if (!EUtils::IsLineEmptyEnemy(TYPEPLANT, line))
			{
				if (VectorIsEmpty(MUtils::AllMowerInline(line)))
				{
					IACreatMower(line);
					return;
				}
			}
		}

		//sinon
		CreatNewTorch(ENTITYRADIUS, false, LIFEPLANT, line);
		IncreasePlantCoin(-(COSTPLANTTORCH + 1));
	}
	else if(nbPlant > 3)
	{
		if (nbPlant > 5)
		{
			std::vector<SunFlower*> allSunFlower = EUtils::AllEntityInline<SunFlower>(line);
			if (allSunFlower.size() > 2)
			{
				IACreatPeatTorch(nbPlant, line);
			}
		}
		else
		{
			IACreatPeatTorch(nbPlant, line);
		}
	}
	else if (nbPlant == 0)
	{
		if (!EUtils::IsLineEmptyEnemy(TYPEPLANT, line))
		{
			IACreatMower(line);
		}
	}
	else if(nbPlant == 1)
	{
		if (!EUtils::IsLineEmptyEnemy(TYPEPLANT, line))
		{
			IACreatPeatTorch(nbPlant, line);
		}
	}
}

void Garden::IACreatPeatTorch(int nbPlant, int line)
{
	if (mPlantCoin > COSTPLANTPEAT)
	{
		if (mPlantCoin > COSTPLANTTORCH)
		{
			if (nbPlant < GenerateRandomNumber(4, 5))
			{
				CreatNewPeat(ENTITYRADIUS, false, LIFEPLANT, line);
				IncreasePlantCoin(-(COSTPLANTPEAT + 1));
			}
			else
			{
				CreatNewTorch(ENTITYRADIUS, false, LIFEPLANT, line);
				IncreasePlantCoin(-(COSTPLANTTORCH + 1));
			}
		}
	}
}

void Garden::IACreatMower(int line)
{
	std::vector<Mower*> allMower = EUtils::AllEntityInline<Mower>(line);
	int lenght = allMower.size();
	for (int i = 0; i < lenght; ++i)
	{
		if (allMower[i]->GetPosition().x == STARTAREACREATMOWER)
		{
			//si existe déja une mower
			return;
		}
	}

	if (mPlantCoin > COSTPLANTMOWER)
	{
		CreatNewMower(ENTITYRADIUS, false, line);
		IncreasePlantCoin(-(COSTPLANTMOWER + 1));
	}
}

void Garden::IaActionZombie()
{
	mTimeZombieCreatProgress -= GetDeltaTime();
	if (mTimeZombieCreatProgress < 0.f)
	{
		mNbCreationZombie++;
		if (mNbCreationZombie > mDifficulty * 50)
		{
			mDifficulty++;
			mNbCreationZombie = 0;
			mTimeZombieCreatProgress = 25.f + (float)mDifficulty * 5.f;
			return;
		}

		int nbLine = NBLINE;
		int nbLineEmpty = 0;
		for (int i = LINEONE; i < LINETHREE + 1; i+=HEIGHTLINE)
		{
			if (EUtils::IsLineEmptyEntity<Plant>(i))
			{
				nbLineEmpty++;
			}
		}

		switch (nbLineEmpty)
		{
		case 0:
			CreatZombieInLineWithNbZombie(nbLine, LINEONE, HEIGHTLINE);
			SetTimeCreatWithDifficulty(mDifficulty);
			break;
		case 1:
			CreatZombieInLineWithNbZombie(nbLine, LINEONE, HEIGHTLINE);
			SetTimeCreatWithDifficulty(mDifficulty);
			break;
		case 2:
			//if(EUtils::IsLineEmptyEntity<Plant>(LINETWO))
			//{
			if (GenerateRandomNumber(0, 1) == 0)
			{
				CreatZombieInLineWithNbZombie(nbLine - 2, LINETHREE, 0);
				SetTimeCreatWithDifficulty(mDifficulty - 1);
			}
			else
			{
				CreatZombieInLineWithNbZombie(nbLine - 2, LINEONE, HEIGHTLINE);
				SetTimeCreatWithDifficulty(mDifficulty - 1);
			}
			//}
			//else
			//{
				//CreatZombieInLineWithNbZombie(nbLine, LINEONE, HEIGHTLINE);
				//SetTimeCreatWithDifficulty(mDifficulty + 2);
			//}
			break;
		}
		mTimeZombieCreatProgress += mTimeZombieCreat;
	}
}

void Garden::CreatZombieInLineWithNbZombie(int nbLine, int firstLine, int betweenLine)
{
	int line = LineUtils::RandomLine(nbLine, firstLine, betweenLine);
	if (EUtils::IsLineEmptyEnemy(TYPEZOMBIE, line))
	{
		if (EUtils::IsLineEmptyEntity<Shot>(line))
		{
			//line vide de shot
			CreatZombieInLineWithNbPlant(line, 0.f);
			CreatZombieInLineWithNbPlant(line, 3.f);
		}
		else
		{
			//line avec des shots
			//donc attendre
			int linenew = line;
			while (line == linenew)
			{
				linenew = LineUtils::RandomLine(nbLine, firstLine, betweenLine);
			}
			CreatZombieInLineWithNbPlant(line, 0.f);
		}
	}
	else
	{
		CreatZombieInLineWithNbPlant(line, 0.f);
	}
}

void Garden::CreatZombieInLineWithNbPlant(int line, float decalX)
{
	int nbPlant = EUtils::NbEntityInLine<Plant>(line);
	if (nbPlant > 9)
	{
		//10 plante
		CreatZombieCone(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE * 10, SPEEDZOMBIE / 2);
	}
	if (nbPlant > 8)
	{
		//9 plante
		if (EUtils::NbEntityInLine<Plant>(line) > 10)
		{
			CreatZombie(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE * 20, SPEEDZOMBIE);
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			int ran = GenerateRandomNumber(0, 5);
			if (ran == 0 || ran == 1)
			{
				CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 10 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
			else
			{
				CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 10 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
				CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 15 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
		else
		{
			CreatZombie(ENTITYRADIUS * 1.5f, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE * 20, SPEEDZOMBIE);
		}
	}
	else if (nbPlant > 6)
	{
		//entre 7 plante et 8 plante
		if (EUtils::NbEntityInLine<Zombie>(line) > 15)
		{
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 10 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			int ran = GenerateRandomNumber(0, 5);
			if (ran == 0 || ran == 1)
			{
				CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 15 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
			else
			{
				CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 15 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
			if (GenerateRandomNumber(0, 5) == 0)
			{
				CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 20 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
				CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 25 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
		else
		{
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 10 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			if (GenerateRandomNumber(0, 5) == 0)
			{
				CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 15 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
	}
	else if (nbPlant > 3)
	{
		//entre 4 plante et 6 plante
		if (EUtils::NbEntityInLine<Zombie>(line) > 20)
		{
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			if (GenerateRandomNumber(0, 5) == 0)
			{
				CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
		else
		{
			CreatZombieCone(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			if (GenerateRandomNumber(0, 5) == 0)
			{
				CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
	}
	else if (nbPlant > 0)
	{
		//entre 1 plante et 3 plante
		if (EUtils::NbEntityInLine<Zombie>(line) > 25)
		{
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			if (GenerateRandomNumber(0, 5) == 0)
			{
				CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + 5 + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
			}
		}
		else
		{
			CreatZombie(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
		}
	}
	else
	{
		// 0 plante
		if (EUtils::NbEntityInLine<Zombie>(line) > 20)
		{
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE * 2);
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE * 2);
		}
		else 
		{
			CreatZombieSport(ENTITYRADIUS, sf::Vector2f(COLLUMZOMBIE + decalX, line), true, LIFEZOMBIE, SPEEDZOMBIE);
		}
	}
}

void Garden::SetTimeCreat(float time)
{
	mTimeZombieCreat = time;
}

void Garden::SetTimeCreatWithDifficulty(int difficulty)
{
	if (difficulty < CREATELOW)
	{
		mTimeZombieCreat = TIMECREATEMICRO;
	}
	else if (CREATEMICRO > difficulty && difficulty < CREATENORMAL)
	{
		mTimeZombieCreat = TIMECREATELOW;
	}
	else if (CREATELOW > difficulty && difficulty < CREATEFAST)
	{
		mTimeZombieCreat = TIMECREATENORMAL;
	}
	else if (CREATENORMAL > difficulty && difficulty < CREATEAPPOCALYPSE)
	{
		mTimeZombieCreat = TIMECREATEFAST;
	}
	else if (CREATEFAST > difficulty && difficulty < CREATEINFINITY)
	{
		mTimeZombieCreat = TIMECREATEAPPOCALYPSE;
	}
	else if (CREATEAPPOCALYPSE > difficulty && difficulty < CREATENOSTOP)
	{
		mTimeZombieCreat = TIMECREATEINFINITY;
	}
	else if (CREATEINFINITY > difficulty)
	{
		mTimeZombieCreat = TIMECREATENOSTOP;
	}
}

float Garden::GetTimeCreat()
{
	return mTimeZombieCreat;
}

bool Garden::GetIaZombie()
{
	return mIaZombie;
}

bool Garden::GetIaPlant()
{
	return mIaPlant;
}

bool Garden::GetIaPlantCreat()
{
	return mIaPlantCreat;
}

void Garden::SetMousePosition(sf::Vector2f mousePos)
{
	mMousePos = mousePos;
}

sf::Vector2f Garden::GetMousePosition()
{
	return mMousePos;
}

void Garden::SetModeCreator(int modeCreator)
{
	mModeCreator = modeCreator;
}

int Garden::GetModeCreator()
{
	return mModeCreator;
}

void Garden::SetCheat(bool cheat)
{
	mCheat = cheat;
}

bool Garden::GetCheat()
{
	return mCheat;
}

void Garden::IncreaseZombiePass()
{
	mZombiePass++;
}

int Garden::GetZombiePass()
{
	return mZombiePass;
}

void Garden::IncreaseZombieDestroy()
{
	mZombieDestroy++;
}

int Garden::GetZombieDestroy()
{
	return mZombieDestroy;
}

void Garden::IncreasePlantEated()
{
	mPlantEated++;
}

int Garden::GetPlantEated()
{
	return mPlantEated;
}

void Garden::IncreasePlantCoin(int more)
{
	mPlantCoin += more;
}

int Garden::GetPlantCoin()
{
	return mPlantCoin;
}

void Garden::IncreaseZombieCoin(int more)
{
	mZombieCoin += more;
}

int Garden::GetZombieCoin()
{
	return mZombieCoin;
}
