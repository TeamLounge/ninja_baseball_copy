#pragma once
#include "bbState.h"

class blueBaseball;


class bbDamagedState :public bbState
{
public:




	int frameCount;

	virtual bbState* inputHandle(blueBaseball* blueBaseball);
	virtual void update(blueBaseball* blueBaseball);
	virtual void enter(blueBaseball* blueBaseball);
	virtual void exit(blueBaseball* blueBaseball);
};

