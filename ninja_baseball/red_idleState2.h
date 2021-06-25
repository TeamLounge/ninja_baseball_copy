#pragma once
#include "playerstate.h"

class red_idleState2 : public playerstate
{
private:
		
	RECT _rc;

	int _count;
	int _index;
	int _rotation;

public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);

};

