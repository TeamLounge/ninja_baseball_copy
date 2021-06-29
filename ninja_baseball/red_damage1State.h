#pragma once
#include "playerstate.h"

class red_damage1State : public playerstate
{
private:

	RECT _rc;
	int _count;
	int _index;
	int _time;

	float _jumpPower;
	float _gravity;
	bool _isLie;

public:

	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

