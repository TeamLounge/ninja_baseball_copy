#pragma once
#include "playerstate.h"
class Ryno_frontCombo : public playerstate
{
private:
	int _count, _index;
	bool isend;
	RECT _rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

