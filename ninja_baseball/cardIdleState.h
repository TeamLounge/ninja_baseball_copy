#pragma once
#include "cardState.h"

class card;

class cardIdleState : public cardState
{
public:
	int frameCount;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);
};

class cardIdleState
{
};

