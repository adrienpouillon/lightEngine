#pragma once
#include "Scene.h"
#include "Mouse.h"

#define ENTITYRADIUS 50 
#define SUNRADIUS 16

#define COLLUMPLANT ENTITYRADIUS*2
#define COLLUMZOMBIE 2020
#define HEIGHTLINE 250
#define LINEONE 100
#define LINETWO HEIGHTLINE + LINEONE
#define LINETHREE HEIGHTLINE + LINETWO
#define NBLINE 3

#define STARTAREACREATPLANT 100
#define BETEWEENPLANT 150
#define NBPLANT 10
#define ENDAREACREATPLANT STARTAREACREATPLANT + (BETEWEENPLANT * NBPLANT)
#define STARTAREACREATMOWER STARTAREACREATPLANT - 112
#define STARTAREACREATSAW STARTAREACREATPLANT + (BETEWEENPLANT/2)
#define ENDAREACREATSAW STARTAREACREATSAW + (BETEWEENPLANT * (NBPLANT - 1))


#define LIFEPLANT 3
#define LIFESHOT 3
#define LIFESHOTROC 3
#define LIFESAW 100
#define LIFEZOMBIE 3
#define LIFEZOMBIECONE 3
#define LIFEZOMBIESPORT 3
#define LIFEZOMBIERA 3
#define LIFEZOMBIESHOT 3

#define COSTZOMBIENORMAL 25 - 1
#define COSTZOMBIECONE 50 - 1
#define COSTZOMBIESPORT 12 - 1
#define COSTZOMBIERA 150 - 1
#define COSTZOMBIESHOT 200 - 1
#define COSTZOMBIEBIG 200 - 1
#define COSTZOMBIECONEBIG 400 - 1
#define COSTPLANTPEAT 100 - 1
#define COSTPLANTTORCH 200 - 1
#define COSTPLANTSUNFLOWER 200 - 1
#define COSTPLANTMOWER 250 - 1
#define COSTPLANTSAW 250 - 1

#define COSTPLANTMINI 100

#define SPEEDZOMBIE 20.f
#define SPEEDSAW 40.f

#define CREATESLEEP 0
#define CREATEMICRO CREATESLEEP + 1
#define CREATELOW CREATEMICRO + 1
#define CREATENORMAL CREATELOW + 2
#define CREATEFAST CREATENORMAL + 3
#define CREATEAPPOCALYPSE CREATEFAST + 5
#define CREATEINFINITY CREATEAPPOCALYPSE + 10
#define CREATENOSTOP CREATEINFINITY + 15

#define TIMECREATENO 100.f
#define TIMECREATEMICRO 2.f
#define TIMECREATELOW 1.5f
#define TIMECREATENORMAL 0.8f
#define TIMECREATEFAST 0.6f
#define TIMECREATEAPPOCALYPSE 0.4f
#define TIMECREATEINFINITY 0.3f
#define TIMECREATENOSTOP 2.f

#define MODEZOMBIE 0
#define MODEPLANT MODEZOMBIE + 1

#define MAXMODECREATOR MODEPLANT + 1

class Shot;

class Garden :public Scene
{
protected:
	std::list<Entity*>* mAllEntity;
	int mModeCreator;
	sf::Vector2f mMousePos;
	Mouse* mMouse;
	int mZombiePass;
	int mZombieDestroy;
	int mPlantEated;
	bool mIaZombie;
	bool mIaPlant;
	bool mIaPlantCreat;
	bool mCheat;
	float mTimeZombieCreat;
	float mTimeZombieCreatProgress;
	int mNbCreationZombie;
	int mDifficulty;
	int mFormerDifficulty;
	int mWave;
	bool mHaveZombieInGame;
	int mPlantCoin;
	int mZombieCoin;
public:
	void OnInitialize();

	void CreatShot(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int life, int type, float verticalDirection);
	void CreatSun(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int type);
	void CreatSun(float radius, sf::Color color, sf::Vector2f pos, bool rigidBody, int type, sf::Vector2f nextPos, float speed);
	void CreatZombie(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);
	void CreatZombieCone(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);
	void CreatZombieSport(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);
	void CreatZombieRa(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);
	void CreatZombieShot(float radius, sf::Vector2f pos, bool rigidBody, int life, float speed);
	void CreatPeat(float radius, sf::Vector2f pos, bool rigidBody, int life);
	void CreatTorch(float radius, sf::Vector2f pos, bool rigidBody, int life);
	void CreatSunFlower(float radius, sf::Vector2f pos, bool rigidBody, int life);
	void CreatMower(float radius, sf::Vector2f pos, bool rigidBody);
	void CreatSaw(float radius, sf::Vector2f pos, bool rigidBody, int life);

	void OnEvent(const sf::Event& event);
	void OnEventMouse(const sf::Event& event);
	void OnEventKeyboard(const sf::Event& event);
	int CreatPlantOrZombie(int costZombie, int costPlant);

	void OnUpdate();

	void DrawPlant();
	void DrawZombie();

	void FallSun(int probability);

	bool TryToErase(Entity* pEntity, float x, float y);
	bool TryCollect(Entity* pEntity, float x, float y);
	bool TryShot(Entity* pEntity, float x, float y);
	bool TryShotRoc(Entity* pEntity, float x, float y);

	void InstanceShot(Entity* itsCreator, float verticalDirection){InstanceShot(itsCreator, verticalDirection, itsCreator->GetPosition());}
	void InstanceShotRoc(Entity* itsCreator, float verticalDirection){InstanceShotRoc(itsCreator, verticalDirection, itsCreator->GetPosition());}
	void InstanceShot(Entity* itsCreator, float verticalDirection, sf::Vector2f pos){InstanceShot(itsCreator, verticalDirection, pos, ENTITYRADIUS / 2);}
	void InstanceShotRoc(Entity* itsCreator, float verticalDirection, sf::Vector2f pos){InstanceShotRoc(itsCreator, verticalDirection, pos, ENTITYRADIUS / 2);}
	void InstanceShot(Entity* itsCreator, float verticalDirection, sf::Vector2f pos, float radiusShot);
	void InstanceShotRoc(Entity* itsCreator, float verticalDirection, sf::Vector2f pos, float radiusShot);
	void InstanceSun(sf::Vector2f pos){CreatSun(SUNRADIUS, sf::Color::Yellow, pos, false, TYPESUN);}
	void InstanceSunDouble(sf::Vector2f pos){CreatSun(SUNRADIUS * 2, sf::Color::Yellow, pos, false, TYPESUN);}
	void InstanceSun(sf::Vector2f pos, sf::Vector2f nextPos) { CreatSun(SUNRADIUS, sf::Color::Yellow, pos, false, TYPESUN, nextPos, 100.f); }
	void InstanceSunDouble(sf::Vector2f pos, sf::Vector2f nextPos) { CreatSun(SUNRADIUS * 2, sf::Color::Yellow, pos, false, TYPESUN, nextPos, 100.f); }

	void CountWave();

	void CreatNewPeat(float radius, bool rigidBody, int life, int line);
	void CreatNewTorch(float radius, bool rigidBody, int life, int line);
	void CreatNewSunFlower(float radius, bool rigidBody, int life, int line);
	void CreatNewMower(float radius, bool rigidBody, int line);
	void CreatNewSaw(float radius, bool rigidBody, int life, int posX);

	void IaActionPlantCreat();
	void IACreatPeatTorch(int nbPlant, int line);
	void IACreatMower(int line);
	void IaActionZombie();

	void CreatZombieInLineWithNbZombie(int nbLine, int firstLine, int betweenLine);
	void CreatZombieInLineWithNbPlant(int line, float decalX);

	void SetTimeCreat(float time);

	void SetTimeCreatWithDifficulty(int difficulty);

	float GetTimeCreat();

	bool GetIaZombie();

	bool GetIaPlant();

	bool GetIaPlantCreat();

	template<typename T>
	T* GetEntity();

	template<typename T>
	std::vector<T*> GetAllEntity();

	template<typename T, typename A>
	static T GetTypeConvert(A TypeA);

	template<typename T, typename A>
	static std::vector<T*> GetAllTypeConvert(std::vector<A*> tabTypeA);

	template<typename T, typename A>
	static std::vector<T*> GetAllTypeConvert(std::list<A*> tabTypeA);

	template<typename T, typename A>
	static std::vector<T*> GetConvertVector(std::vector<A*> tabTypeA);

	template<typename T>
	static bool VectorIsEmpty(std::vector<T*> tabTypeA);

	void SetMousePosition(sf::Vector2f mousePos);

	sf::Vector2f GetMousePosition();

	void SetModeCreator(int modeCreator);

	int GetModeCreator();

	void SetCheat(bool cheat);

	bool GetCheat();

	void IncreaseZombiePass();

	int GetZombiePass();

	void IncreaseZombieDestroy();

	int GetZombieDestroy();

	void IncreasePlantEated();

	int GetPlantEated();

	void IncreasePlantCoin(int more);

	int GetPlantCoin();

	void IncreaseZombieCoin(int more);

	int GetZombieCoin();

};

template<typename T>
inline T* Garden::GetEntity()
{
	for (int i = 0; i < mAllEntity.size(); ++i)
	{
		if (T* entity = dynamic_cast<T*>(mAllEntity[i]))
		{
			return entity;
		}
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> Garden::GetAllEntity()
{
	std::vector<T*> allT;
	for (auto it = (*mAllEntity).begin(); it != (*mAllEntity).end(); )
	{
		if (T* entity = dynamic_cast<T*>(*it))
		{
			allT.push_back(entity);
		}
		++it;
	}
	return allT;
}

template<typename T, typename A>
inline T Garden::GetTypeConvert(A TypeA)
{
	if (T entityConvert = dynamic_cast<T>(TypeA))
	{
		return entityConvert;
	}
	return nullptr;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetAllTypeConvert(std::vector<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	int lenght = (int)tabTypeA.size();
	for (int i = 0; i < lenght; ++i)
	{
		if (T* entityConvert = dynamic_cast<T*>(tabTypeA[i]))
		{
			allTypeT.push_back(entityConvert);
		}
	}
	return allTypeT;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetAllTypeConvert(std::list<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	for (auto it = (tabTypeA).begin(); it != (tabTypeA).end(); )
	{
		if (T* entityConvert = dynamic_cast<T*>(*it))
		{
			allTypeT.push_back(entityConvert);
		}
		++it;
	}
	return allTypeT;
}

template<typename T, typename A>
inline std::vector<T*> Garden::GetConvertVector(std::vector<A*> tabTypeA)
{
	std::vector<T*> allTypeT;
	for (int i = 0; i < (int)tabTypeA.size(); ++i)
	{
		allTypeT.push_back(tabTypeA[i]);
	}
	return allTypeT;
}

template<typename T>
inline bool Garden::VectorIsEmpty(std::vector<T*> tabTypeA)
{
	if ((int)tabTypeA.size() == 0)
	{
		return true;
	}
	return false;
}


