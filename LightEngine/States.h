#pragma once
#include "StateManager.h"

class States
{
protected:
	StateManager* mStateManager;
public:
	States(StateManager* stateManager);

	virtual void Start() = 0;

	virtual void Update(float deltaTime) = 0;
};



class FullState :public States
{
protected:
	float mIdleTime;
	float mIdleProgress;
public:
	FullState(float idleTime, StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

	void SetTimeProgress(float idleProgress);
};



class LoadedState :public States
{
protected:
	float mIdleTime;
	float mIdleProgress;
public:
	LoadedState(float idleTime, StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

	void SetTimeProgress(float idleProgress);
};



class EmptyState :public States
{
protected:
	float mIdleTime;
	float mIdleProgress;
public:
	EmptyState(float idleTime, StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

	void SetTimeProgress(float idleProgress);

};



class ShootingState :public States
{
protected:
	float mShootProgress;
	float mShootTime;
public:
	ShootingState(float shootTime, StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

	void SetShootProgress(float shootProgress);

};




class ReloadingState :public States
{
protected:
	float mReloadProgress;
	float mReloadTime;
public:
	ReloadingState(float reloadTime, StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

	void SetReloadProgress(float reloadingProgress);

};




class WalkingState :public States
{
protected:

public:
	WalkingState(StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

};




class EatingState :public States
{
protected:
	
public:
	EatingState(StateManager* stateManager);

	virtual void Start();

	virtual void Update(float deltaTime);

};



