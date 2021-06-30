#pragma once
#include "gbState.h"

class greenBaseball;

class gbDamagedState :public gbState
{
public:

	int frameCount;

	virtual gbState* inputHandle(greenBaseball* greenBaseball);
	virtual void update(greenBaseball* greenBaseball);
	virtual void enter(greenBaseball* greenBaseball);
	virtual void exit(greenBaseball* greenBaseball);
};

