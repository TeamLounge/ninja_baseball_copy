#pragma once
#include "bossState.h"

class boss;

class bossSmallDamagedState : public bossState
{
public:
	int frameCount;
	int readyCount;
	int deathCount;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);
};
