#pragma once
#include "playerstate.h"
class Ryno_death : public playerstate
{
private:
	int _count, _index;
	float jumpPower, gravity;

	RECT rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

