#pragma once
#include "playerstate.h"
class Ryno_fall : public playerstate
{
private:
	int _count, _index;
	float _jumpPower, _gravity;
	bool isattack;
	RECT rc;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

