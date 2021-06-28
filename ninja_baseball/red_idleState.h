#pragma once
#include "playerstate.h"

class red_idleState : public playerstate
{
private:
	RECT _rc;
	int _count;
	int _index;
	int _time;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

