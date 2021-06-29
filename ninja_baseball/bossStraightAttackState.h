#pragma once
#include "bossState.h"

class boss;

class bossStraightAttackState : public bossState
{
public:
	int frameCount;
	int readyCount;
	float dashPower;
	float friction;
	

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);

	void move(boss* boss);
};
