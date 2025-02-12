#include "StateManager.h"
#include <iostream>
#include "States.h"

StateManager::StateManager()
{
}

void StateManager::Init(int capacity, int reloadTime, int shootTime, int modeUse, Entity* id)
{
	//mode use
	//modeUse = NOUSE = 0 -> rien
	//modeUse = SHOOTINGUSE = 1 -> shooting uniquement
	//modeUse = WALKINGUSE = 2 -> walking uniquement
	//modeUse = SHOOTTINGWALKINGUSE = 3 -> shooter + walking

	mThis = id;
	if (modeUse == SHOOTINGUSE || modeUse == SHOOTTINGWALKINGUSE)
	{
		mAllState.push_back(new FullState(this));
		mAllState.push_back(new LoadedState(this));
		mAllState.push_back(new EmptyState(this));
		mAllState.push_back(new ReloadingState(reloadTime, this));
		mAllState.push_back(new ShootingState(shootTime, this));

		mCapacity = capacity;
		mAmmo = mCapacity;
	}
	else
	{
		mAllState.push_back(nullptr);
		mAllState.push_back(nullptr);
		mAllState.push_back(nullptr);
		mAllState.push_back(nullptr);
		mAllState.push_back(nullptr);

		mCapacity = 0;
		mAmmo = mCapacity;
	}

	if (modeUse == WALKINGUSE || modeUse == SHOOTTINGWALKINGUSE)
	{
		mAllState.push_back(new WalkingState(this));
		mAllState.push_back(new EatingState(this));
	}
	else
	{
		mAllState.push_back(nullptr);
		mAllState.push_back(nullptr);
	}

	SetAllColor(sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White);

	mCapacity = capacity;
	mAmmo = capacity;
}

void StateManager::OnUpdate(float deltaTime)
{
	Update(deltaTime);
}

void StateManager::Update(float deltaTime)
{
	switch (mState)
	{
	case State::Full:
		IsFull();
		break;
	case State::Loaded:
		IsLoaded();
		break;
	case State::Empty:
		IsEmpty();
		break;
	case State::Shooting:
		if (ShootingState* shooting = GetState<ShootingState>())
		{
			shooting->Update(deltaTime);
		}
		IsShooting();
		break;
	case State::Reloading:
		if (ReloadingState* reloading = GetState<ReloadingState>())
		{
			reloading->Update(deltaTime);
		}
		IsReloading();
		break;
	case State::Walking:
		if (WalkingState* walking = GetState<WalkingState>())
		{
			walking->Update(deltaTime);
		}
		IsWalking();
		break;
	case State::Eating:
		if (EatingState* eating = GetState<EatingState>())
		{
			eating->Update(deltaTime);
		}
		IsEating();
		break;
	}
	SetIsCollide(false);
}

bool StateManager::TransitionTo(State newState)
{
	int currenteStateIndex = static_cast<int>(mState);
	int newStateIndex = static_cast<int>(newState);

	if (mTransition[currenteStateIndex][newStateIndex] == 0)
	{
		return false;
	}

	mState = newState;

	return true;
}

void StateManager::IsFull()
{
	mThis->GetShape()->setFillColor(mColor[0]);
}
void StateManager::IsLoaded()
{
	mThis->GetShape()->setFillColor(mColor[1]);
}
void StateManager::IsEmpty()
{
	mThis->GetShape()->setFillColor(mColor[2]);
}
void StateManager::IsShooting()
{
	mThis->GetShape()->setFillColor(mColor[3]);
}
void StateManager::IsReloading()
{
	mThis->GetShape()->setFillColor(mColor[4]);
}
void StateManager::IsWalking()
{
	mThis->GetShape()->setFillColor(mColor[5]);
}
void StateManager::IsEating()
{
	mThis->GetShape()->setFillColor(mColor[6]);
}

void StateManager::SetAllColor(sf::Color full, sf::Color loaded, sf::Color empty, sf::Color shoot, sf::Color reload, sf::Color walk, sf::Color eat)
{
	mColor.push_back(full);
	mColor.push_back(loaded);
	mColor.push_back(empty);
	mColor.push_back(shoot);
	mColor.push_back(reload);
	mColor.push_back(walk);
	mColor.push_back(eat);
}

void StateManager::Shoot()
{
	//si peut tirer
	if (TransitionTo(State::Shooting))
	{
		//tirer
		if (ShootingState* shooting = GetState<ShootingState>())
		{
			shooting->Start();
		}
		AmmoLessLess();
		OnShoot();
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

void StateManager::Reload()
{
	//si peut recharger
	if (TransitionTo(State::Reloading))
	{
		//recharger
		if (ReloadingState* reloading = GetState<ReloadingState>())
		{
			reloading->Start();
		}
		SetMaxAmmo();
		std::cout << "recharge de munition" << std::endl;
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

void StateManager::OnShoot(){}

void StateManager::SetIsCollide(bool isCollide)
{
	mIsCollide = isCollide;
}

bool StateManager::GetIsCollide()
{
	return mIsCollide;
}

void StateManager::SetAmmo(int ammo)
{
	mAmmo = ammo;
}

void StateManager::SetMaxAmmo()
{
	SetAmmo(mCapacity);
}

void StateManager::AmmoLessLess()
{
	SetAmmo(mAmmo - 1);
}

int StateManager::GetAmmo()
{
	return mAmmo;
}

Entity* StateManager::GetThis()
{
	return mThis;
}

void StateManager::Destroy()
{
	delete this;
}

StateManager::~StateManager()
{
	int lenght = mAllState.size();
	for (int i = 0; i < lenght; i++)
	{
		delete mAllState[i];
	}
}
