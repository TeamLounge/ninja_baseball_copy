#pragma once
#include "playerstate.h"

class red_gripState : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _index;
	bool _isMove;

public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

