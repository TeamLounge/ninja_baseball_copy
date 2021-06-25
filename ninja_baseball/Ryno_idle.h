#pragma once
#include "playerstate.h"

class Ryno_idle : public playerstate
{
private:
	int _count, _time, _index , _Rotation;

public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

