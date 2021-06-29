#pragma once
#include "wbState.h"


class whiteBaseball;

class wbAttackJumpState :public wbState
{
public:

	int frameCount;

	float jumpPower;
	float gravity;
	
	virtual wbState* inputHandle(whiteBaseball* whiteBaseball);
	virtual void update(whiteBaseball* whiteBaseball);
	virtual void enter(whiteBaseball* whiteBaseball);
	virtual void exit(whiteBaseball* whiteBaseball);

	void jump(whiteBaseball * whiteBaseball);

};
