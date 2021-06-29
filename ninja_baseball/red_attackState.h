#pragma once
#include "playerstate.h"

class red_attackState : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _index;
	int _time;
	int _attackCount;
	bool _isend;

	RECT _attackRc1;
	RECT _attackRc2;
	RECT _attackRc3;
	
public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

