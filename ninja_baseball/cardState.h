#pragma once
#include "gameNode.h"

class card;

class cardState
{
public:
	virtual cardState* inputHandle(card* card) = 0;
	virtual void update(card* card) = 0;
	virtual void enter(card* card) = 0;
	virtual void exit(card* card) = 0;
};

