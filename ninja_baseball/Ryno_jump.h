#pragma once
#include "playerstate.h"

class Ryno_jump : public playerstate
{
private:
	int _count, _index;
	float _jumpPower, _gravity;
	bool isattack;
public:
	virtual playerstate* handleInput(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
};

