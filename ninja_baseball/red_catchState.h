#pragma once
#include "playerstate.h"

class red_catchState : public playerstate
{
private:
	RECT _rc;
	int _time;
	bool _isAtkOn;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

