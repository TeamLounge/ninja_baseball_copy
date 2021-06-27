#pragma once
#include "gbState.h"

class greenBaseball;

class gbIdleState :public gbState
{
public:

	int frameCount;
	int timeCount;

	virtual gbState* inputHandle(greenBaseball* greenBaseball);
	virtual void update(greenBaseball* greenBaseball);
	virtual void enter(greenBaseball* greenBaseball);
	virtual void exit(greenBaseball* greenBaseball);
};
