#pragma once
#include "wbState.h"


class whiteBaseball;

class wbStopState :public wbState
{
public:

	int frameCount;

	float speed;
	float friction;

	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);


};

class wbStopState
{
};

