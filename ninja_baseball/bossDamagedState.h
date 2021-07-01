#pragma once
#include "bossState.h"

class boss;

class bossDamagedState : public bossState
{
public:
	int frameCount;
	int readyCount;
	float jumpPower;
	float gravity;
	int deathCount;
	float moveX;
	int catchCount;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);

	void jump(boss* boss);
};
