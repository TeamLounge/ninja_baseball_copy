#pragma once
#include "playerstate.h"

class Ryno_move : public playerstate
{
private:
	int _count, _index;
	RECT _rc;
	bool LEFT, RIGHT, UP, DOWN;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

