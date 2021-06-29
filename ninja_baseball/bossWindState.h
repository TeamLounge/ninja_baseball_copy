#pragma once
#include "bossState.h"

class boss;

class bossWindState : public bossState
{
public:
	int frameCount;
	float jumpPower;
	float gravity;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);

	void flying(boss* boss);
};


