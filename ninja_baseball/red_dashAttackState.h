#pragma once
#include "playerstate.h"

class red_dashAttackState : public playerstate
{
private:
	RECT _rc;
	int _time;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

