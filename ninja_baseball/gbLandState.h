#pragma once

#include "gbState.h"

class greenBaseball;

class gbLandState :public gbState
{
public:

	int frameCount;
	float speed = 7;

	float jumpPower;
	float gravity;

	virtual gbState* inputHandle(greenBaseball* greenBaseball);
	virtual void update(greenBaseball* greenBaseball);
	virtual void enter(greenBaseball* greenBaseball);
	virtual void exit(greenBaseball* greenBaseball);

	void gbJump(greenBaseball* greenBaseball);
};
