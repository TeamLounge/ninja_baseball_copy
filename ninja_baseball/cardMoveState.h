#pragma once
#include "cardState.h"

class card;

class cardMoveState : public cardState
{
public:
	int frameCount;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);

	void isSide(card* card);
	void move(card* card);
};

class cardMoveState
{
};

class cardMoveState
{
};

