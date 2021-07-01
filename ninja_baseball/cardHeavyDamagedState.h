#pragma once
#include "cardState.h"

class card;

class cardHeavyDamagedState : public cardState
{
public:
	int frameCount;
	int readyCount;
	float jumpPower;
	float gravity;
	int deathCount;
	float moveX;
	int catchCount;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);
};
