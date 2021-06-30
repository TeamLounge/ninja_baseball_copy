#pragma once
#include "ybState.h"

class yellowBaseball;

class ybAttackPunchState :public ybState
{
public:

	int frameCount;

	virtual ybState* inputHandle(yellowBaseball* yellowBaseball);
	virtual void update(yellowBaseball* yellowBaseball);
	virtual void enter(yellowBaseball* yellowBaseball);
	virtual void exit(yellowBaseball* yellowBaseball);
};
