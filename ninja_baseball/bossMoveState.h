#pragma once
#include "bossState.h"

class boss;

class bossMoveState : public bossState
{
public:
	int frameCount;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
};

