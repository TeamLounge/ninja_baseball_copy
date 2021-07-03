#pragma once
#include "bossState.h"

class boss;

class bossDeathState : public bossState
{
public:
	int frameCount;
	int readyCount;
	float jumpPower;
	float gravity;
	float moveX;
	int count;
	bool _soundOn;

	virtual bossState* inputHandle(boss* boss);
	virtual void update(boss* boss);
	virtual void enter(boss* boss);
	virtual void exit(boss* boss);

	void jump(boss* boss);
};

