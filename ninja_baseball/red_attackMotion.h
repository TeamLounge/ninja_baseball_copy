#pragma once
#include "playerstate.h"

class red_attackMotion : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _index;

public:

	playerstate* handleInpunt(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

