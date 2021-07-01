#pragma once
#include "playerstate.h"

class red_fallState : public playerstate
{
private:
	RECT _rc;
	int _index;
	float _jumpPower;
	float _gravity;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

