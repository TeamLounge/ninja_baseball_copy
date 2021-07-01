#pragma once
#include "playerstate.h"

#define redSpeed 5

class red_moveState : public playerstate
{
private:
	RECT _rc;
	int _count;
	int _index;
	int _runTime;
	bool _runTimeStart;
	bool _isRun;
	bool _isRight;
	bool _isLeft;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

