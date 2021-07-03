#pragma once
#include "playerstate.h"

class red_startState : public playerstate
{
private:
	RECT _rc;
	int _time;
	int _count;
	int _index;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

