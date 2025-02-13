#include "States.h"
#include <iostream>

States::States(StateManager* stateManager)
{
	mStateManager = stateManager;
}





FullState::FullState(float idleTime, StateManager* stateManager) : States(stateManager), mIdleTime(idleTime), mIdleProgress(idleTime)
{
}

void FullState::Start()
{
	SetTimeProgress(mIdleTime);
}

void FullState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanShoot(true);
	}
}

void FullState::SetTimeProgress(float idleProgress)
{
	mIdleProgress = idleProgress;
}




LoadedState::LoadedState(float idleTime, StateManager* stateManager) : States(stateManager), mIdleTime(idleTime), mIdleProgress(idleTime)
{
}

void LoadedState::Start()
{
	SetTimeProgress(mIdleTime);
}

void LoadedState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanShoot(true);
		mStateManager->SetCanReload(true);
	}
}

void LoadedState::SetTimeProgress(float idleProgress)
{
	mIdleProgress = idleProgress;
}




EmptyState::EmptyState(float idleTime, StateManager* stateManager) : States(stateManager), mIdleTime(idleTime), mIdleProgress(idleTime)
{
}

void EmptyState::Start()
{
	SetTimeProgress(mIdleTime);
}

void EmptyState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanReload(true);
	}
}

void EmptyState::SetTimeProgress(float idleProgress)
{
	mIdleProgress = idleProgress;
}



ShootingState::ShootingState(float shootTime, StateManager* stateManager) : States(stateManager), mShootTime(shootTime), mShootProgress(shootTime)
{

}

void ShootingState::Start()
{
	SetShootProgress(mShootTime);
}

void ShootingState::Update(float deltaTime)
{
	mShootProgress -= deltaTime;
	if (mShootProgress < 0.f)
	{
		if (mStateManager->GetAmmo() <= 0)
		{
			if (mStateManager->TransitionTo(mStateManager->State::Empty))
			{
				if (EmptyState* empty = mStateManager->GetState<EmptyState>())
				{
					empty->Start();
				}
			}
		}
		else
		{
			if (mStateManager->TransitionTo(mStateManager->State::Loaded))
			{
				if (LoadedState* loaded = mStateManager->GetState<LoadedState>())
				{
					loaded->Start();
				}
			}
		}
	}
}

void ShootingState::SetShootProgress(float shootProgress)
{
	mShootProgress = shootProgress;
}




ReloadingState::ReloadingState(float reloadTime, StateManager* stateManager) : States(stateManager), mReloadTime(reloadTime), mReloadProgress(reloadTime)
{

}

void ReloadingState::Start()
{
	SetReloadProgress(mReloadTime);
}

void ReloadingState::Update(float deltaTime)
{
	mReloadProgress -= deltaTime;
	if (mReloadProgress < 0.f)
	{
		if (mStateManager->TransitionTo(mStateManager->State::Full))
		{
			if (FullState* full = mStateManager->GetState<FullState>())
			{
				full->Start();
			}
		}
	}
}

void ReloadingState::SetReloadProgress(float reloadProgress)
{
	mReloadProgress = reloadProgress;
}




WalkingState::WalkingState(StateManager* stateManager) : States(stateManager)
{

}

void WalkingState::Start()
{
	Entity* entity = mStateManager->GetThis();
	sf::Vector2f direction = entity->GetDirection();
	float speed = entity->GetSpeed();
	entity->GoToDirection(direction.x, direction.y, speed);
}

void WalkingState::Update(float deltaTime)
{
	if (mStateManager->GetIsCollide() == true)
	{
		if (mStateManager->TransitionTo(mStateManager->State::Eating))
		{
			Entity* entity = mStateManager->GetThis();
			entity->SetSpeed(0);
			if (EatingState* eating = mStateManager->GetState<EatingState>())
			{
				eating->Start();
			}
		}
	}
}




EatingState::EatingState(StateManager* stateManager) : States(stateManager)
{

}

void EatingState::Start()
{

}

void EatingState::Update(float deltaTime)
{
	if (mStateManager->GetIsCollide() == false)
	{
		if (mStateManager->TransitionTo(mStateManager->State::Walking))
		{
			if (WalkingState* walking = mStateManager->GetState<WalkingState>())
			{
				walking->Start();
			}
		}
	}
}