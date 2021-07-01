#pragma once
#include "cardState.h"

class card;

class cardSmallDamagedState : public cardState
{
public:
	int frameCount;
	int readyCount;
	int deathCount;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);
};

