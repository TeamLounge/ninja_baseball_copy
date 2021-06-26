#pragma once
#include "wbState.h"


class whiteBaseball;

class wbRollState :public wbState
{
public:

	int frameCount;
	float speed = 10;

	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);

	void wbMove(whiteBaseball* whiteBaseball);

};
