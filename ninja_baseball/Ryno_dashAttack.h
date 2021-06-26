#pragma once
#include "playerstate.h"
class Ryno_dashAttack : public playerstate
{
private:
	int _count, _index;
	RECT _rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

