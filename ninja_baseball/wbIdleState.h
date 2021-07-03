#pragma once
#include "wbState.h"

class whiteBaseball;

class wbIdleState :public wbState
{
public:

	int frameCount;

	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);
};
