#pragma once
#include "playerstate.h"

class red_attck : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _startIndex;
	int _endIndex;
	int _attackCount;

public:

	playerstate* handleInpunt(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

