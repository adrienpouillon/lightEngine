#include "States.h"

States::States(StateManager* stateManager)
{
	mStateManager = stateManager;
}





FullState::FullState(StateManager* stateManager) : States(stateManager)
{
}

void FullState::Start()
{
}

void FullState::Update(float deltaTime)
{

}




LoadedState::LoadedState(StateManager* stateManager) : States(stateManager)
{
}

void LoadedState::Start()
{
}

void LoadedState::Update(float deltaTime)
{

}




EmptyState::EmptyState(StateManager* stateManager) : States(stateManager)
{
}

void EmptyState::Start()
{
}

void EmptyState::Update(float deltaTime)
{

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
			entity->GoToDirection(0, 0, 0.f);
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