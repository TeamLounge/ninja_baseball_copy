#pragma once
#include "playerstate.h"

class red_jumpAttackState : public playerstate
{
private:
	RECT _rc;
	int _count;
	int _index;
		
public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

