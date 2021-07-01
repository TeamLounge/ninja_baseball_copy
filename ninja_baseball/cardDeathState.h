#pragma once
#include "cardState.h"

class card;

class cardDeathState : public cardState
{
public:
	int frameCount;
	int readyCount;
	float jumpPower;
	float gravity;
	float moveX;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);

	void jump(card* card);
};


