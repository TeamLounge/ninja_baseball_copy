#pragma once
#include "playerstate.h"
class Ryno_damage : public playerstate
{
private:
	int _count, _time, _index;
	bool isend;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

