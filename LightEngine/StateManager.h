#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"


#define NOUSE 0 
#define SHOOTINGUSE NOUSE + 1
#define WALKINGUSE SHOOTINGUSE + 1
#define SHOOTTINGWALKINGUSE WALKINGUSE + 1

class States;

class StateManager
{
public:
	enum State
	{
		//si max de ball
		Full,
		//si as des balls
		Loaded,
		//si vide de ball
		Empty,
		//si en tire
		Shooting,
		//si en rechargement
		Reloading,
		//si en deplacement
		Walking,
		//si en degustation
		Eating,

		Count
	};
	static constexpr int StateCount = static_cast <int>(State::Count);

protected:
	int mAmmo;
	int mCapacity;
	bool mCanShoot;
	bool mCanReload;

	bool mIsCollide;

	std::vector<sf::Color> mColor;
	Entity* mThis;
	

	std::vector<States*> mAllState;
	/*const char** mAllState;*/

	State mState;

	int mTransition[StateCount][StateCount] =
	{
	//	Full,Loaded,Empty,Shooting,Reloading,Walking,Eating
		{0,		0,		0,		1,		0,		1,		1 },//Full
		{0,		0,		0,		1,		1,		1,		1 },//Loaded
		{0,		0,		0,		0,		1,		1,		1 },//Empty
		{0,		1,		1,		0,		0,		0,		0 },//Shooting
		{1,		0,		0,		0,		0,		0,		0 },//Reloading
		{0,		0,		0,		1,		1,		0,		1 },//Walking
		{0,		0,		0,		0,		0,		1,		0 }//Eating
	};

public:
	StateManager();

	void Init(int capacity, float reloadTime, float shootTime, float idletime, int modeUse, Entity* id);

	void OnUpdate(float deltaTime);

	void Update(float deltaTime);

	bool TransitionTo(State newState);

	virtual void IsFull();
	virtual void IsLoaded();
	virtual void IsEmpty();
	virtual void IsShooting();
	virtual void IsReloading();
	virtual void IsWalking();
	virtual void IsEating();

	void SetAllColor(sf::Color full, sf::Color loaded, sf::Color empty, sf::Color shoot, sf::Color reload, sf::Color walk, sf::Color eat);

	void Shoot(int tag);

	void Reload();

	virtual void OnShoot(int tag);

	void SetIsCollide(bool isCollide);

	bool GetIsCollide();

	void SetAmmo(int ammo);

	void SetMaxAmmo();

	void AmmoLessLess();

	int GetAmmo();

	Entity* GetThis();

	template<typename T>
	T* GetState();

	void SetCanShoot(bool canShoot);

	bool GetCanShoot();

	void SetCanReload(bool canReload);

	bool GetCanReload();

	~StateManager();
};

template<typename T>
inline T* StateManager::GetState()
{
	for (int i = 0; i < mAllState.size(); ++i)
	{
		if (T* state = dynamic_cast<T*>(mAllState[i]))
		{
			return state;
		}
	}
	return nullptr;
}


