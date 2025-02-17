#pragma once
#include "Entity.h"
class Mouse :public Entity
{
protected:

public:
	void OnInitialize();

	virtual void OnUpdate();

	virtual int GetType();

};

