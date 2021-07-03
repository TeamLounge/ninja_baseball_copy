#pragma once
#include "wbState.h"


class whiteBaseball;

class wbDeathState : public wbState
{
public:

	int frameCount;
	int count;

	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);
};

