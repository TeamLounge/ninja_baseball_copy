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
	bool _isRightWall;
	bool _isLeftWall;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);

	void jump(card* card);
};
