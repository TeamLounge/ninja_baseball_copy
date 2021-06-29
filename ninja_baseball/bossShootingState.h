#pragma once
#include "bossState.h"

class boss;

class bossShootingState : public bossState
{
public:
	int frameCount;
	int _fireX;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
};
