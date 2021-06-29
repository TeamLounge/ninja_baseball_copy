#pragma once
#include "gameNode.h"

class boss;

class bossState
{
public:
	virtual bossState* inputHandle(boss* boss) = 0;
	virtual void update(boss* boss) = 0;
	virtual void enter(boss* boss) = 0;
	virtual void exit(boss* boss) = 0;
};

