#include "States.h"
#include <iostream>
#include "Garden.h"

States::States(StateManager* stateManager)
{
	mStateManager = stateManager;
}





FullState::FullState(float idleTime, StateManager* stateManager) : States(stateManager), mIdleTime(idleTime), mIdleProgress(idleTime)
{
}

void FullState::Start()
{
	if (mStateManager->GetThis()->GetScene<Garden>()->GetIaPlant() == false)
	{
		SetTimeProgress(0.f);
		return;
	}

	SetTimeProgress(mIdleTime);
}

void FullState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanShoot(true);
		mStateManager->SetCanBoost(true);

		if ((*mStateManager->GetAllState())[mStateManager->State::Walking] != nullptr)
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
	if (mStateManager->GetThis()->GetScene<Garden>()->GetIaPlant() == false)
	{
		SetTimeProgress(0.f);
		return;
	}

	SetTimeProgress(mIdleTime);
}

void LoadedState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanShoot(true);
		mStateManager->SetCanBoost(true);
		mStateManager->SetCanReload(true);

		if ((*mStateManager->GetAllState())[mStateManager->State::Walking] != nullptr)
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
	if (mStateManager->GetThis()->GetScene<Garden>()->GetIaPlant() == false)
	{
		SetTimeProgress(0.f);
		return;
	}

	SetTimeProgress(mIdleTime);
}

void EmptyState::Update(float deltaTime)
{
	mIdleProgress -= deltaTime;
	if (mIdleProgress < 0.f)
	{
		mStateManager->SetCanReload(true);

		if ((*mStateManager->GetAllState())[mStateManager->State::Walking] != nullptr)
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
}

void EmptyState::SetTimeProgress(float idleProgress)
{
	mIdleProgress = idleProgress;
}



ActioningState::ActioningState(float actioningTime, StateManager* stateManager) : States(stateManager), mActioningTime(actioningTime), mActioningProgress(actioningTime)
{

}

void ActioningState::Start()
{
	SetActioningProgress(mActioningTime);
}

void ActioningState::Update(float deltaTime)
{
	mActioningProgress -= deltaTime;
	if (mActioningProgress < 0.f)
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

void ActioningState::SetActioningProgress(float actioningProgress)
{
	mActioningProgress = actioningProgress;
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




WalkingState::WalkingState(float speed, float walkingTime,  StateManager* stateManager) : States(stateManager), mSpeed(speed), mWalkingTime(walkingTime)
{

}

void WalkingState::Start()
{
	Entity* entity = mStateManager->GetThis();
	entity->SetSpeed(mSpeed);
	SetWalkingProgress(mWalkingTime);
}

void WalkingState::Update(float deltaTime)
{
	mWalkingProgress -= deltaTime;
	if(mWalkingProgress < 0.f)
	{
		if ((*mStateManager->GetAllState())[mStateManager->State::Actioning] != nullptr)
		{
			if(mStateManager->GetAmmo())
			{
				mStateManager->SetCanShoot(true);
				mStateManager->SetCanBoost(true);
			}
			mStateManager->SetCanReload(true);
		}

		if (mStateManager->GetIsCollide() == true)
		{
			if (mStateManager->TransitionTo(mStateManager->State::Eating))
			{
				Entity* entity = mStateManager->GetThis();
				entity->SetSpeed(0.f);
				if (EatingState* eating = mStateManager->GetState<EatingState>())
				{
					eating->Start();
				}
			}
		}
	}
}

void WalkingState::SetWalkingProgress(float walkingProgress)
{
	mWalkingProgress = walkingProgress;
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