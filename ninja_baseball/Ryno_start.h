#pragma once
#include "playerstate.h"
class Ryno_start : public playerstate
{
private:
	int _count;
	RECT _rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

