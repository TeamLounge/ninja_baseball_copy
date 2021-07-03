#pragma once
#include "playerstate.h"

class red_gripState : public playerstate
{
private:

	RECT _rc;
	RECT _atkRc;
	int _count;
	int _index;
	bool _isMove;
	bool _isGrip;

public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

