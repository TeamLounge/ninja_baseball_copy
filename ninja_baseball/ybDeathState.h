#pragma once
#include "ybState.h"

class yellowBaseball;

class ybDeathState : public ybState
{
public:

	int frameCount;
	int count;

	virtual ybState* inputHandle(yellowBaseball* yellowBaseball);
	virtual void update(yellowBaseball* yellowBaseball);
	virtual void enter(yellowBaseball* yellowBaseball);
	virtual void exit(yellowBaseball* yellowBaseball);
};

