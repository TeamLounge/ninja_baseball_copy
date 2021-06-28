#pragma once
#include "playerstate.h"

class red_homeRunState : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _index;
	int _count2;

public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

