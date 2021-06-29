#pragma once
#include "gloveState.h"

class glove;

class gloveJumpState :public gloveState
{
public:

	int frameCount;
	int delayCnt;

	float jumpPower;
	float gravity;


	virtual gloveState* inputHandle(glove* glove);
	virtual void update(glove* glove);
	virtual void enter(glove* glove);
	virtual void exit(glove* glove);

	void jumpAppear(glove* glove);


};
