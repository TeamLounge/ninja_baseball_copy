#pragma once
#include "cardState.h"

class card;

class cardDashAttackState : public cardState
{
public:
	int frameCount;
	int _atkCount;
	float _accel;
	float _speed;
	bool _isRightDash;
	bool _isLeftDash;
	bool _isRightWall;
	bool _isLeftWall;

	virtual cardState* inputHandle(card* card);
	virtual void update(card* card);
	virtual void enter(card* card);
	virtual void exit(card* card);

	void dashMove(card* card);
};
