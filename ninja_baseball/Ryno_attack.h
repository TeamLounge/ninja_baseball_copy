#pragma once
#include "playerstate.h"
class Ryno_attack :public playerstate
{
private:
	int _count, _index;
	bool isend;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

