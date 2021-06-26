#pragma once
#include "playerstate.h"
class Ryno_fly : public playerstate
{
private:
	int _count, _index;
	int _actiontime , _commandTime;

	float _jumpPower, _gravity;
	float _top;
	bool isattack , isend ,next;
	RECT rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

