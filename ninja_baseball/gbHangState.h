#pragma once

#include "gbState.h"

class greenBaseball;

class gbHangState :public gbState
{
public:

	int frameCount;
	int timeCount;

	float speed = 3;
	float jumpPower;
	float gravity;

	virtual gbState* inputHandle(greenBaseball* greenBaseball);
	virtual void update(greenBaseball* greenBaseball);
	virtual void enter(greenBaseball* greenBaseball);
	virtual void exit(greenBaseball* greenBaseball);
	
	void gbStart(greenBaseball* greenBaseball);
};

