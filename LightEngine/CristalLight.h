#pragma once
#include "Plant.h"
struct ShotVariable
{
	int mRadius;
	int mLife;
	float mLine;
	int mCost;
};

class CristalLight :public Plant
{
protected:
	int mCoin;
	ShotVariable mShotVarible;
	float mTimeSunProgress;
public:
	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	void MoreCoin();

	virtual void IaAction();

	virtual void OnShoot(int tag);

	void IncreaseCoin(int coin);

	int GetCoin();

};

