#pragma once
#include "Plant.h"
#include "Garden.h"

class Shot;

class Torch :public Plant
{
protected:
	Shot* mShot;
public:

	void OnInitialize();

	virtual void OnCollision(Entity* other);

	virtual void OnUpdate();

	virtual void ActionDead();

	virtual void IaAction();

	void EnemyAlmost(int tagAlmost, int tagFar, int tagUp, int tagDown);

	bool IsLineUpDownHaveDanger(int tagUp, int tagDown);

	bool EnemyInLineUpDown(int tagUp, int tagDown);

	void OnBoost(int tag);

};

