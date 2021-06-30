#pragma once
#include "playerstate.h"

class red_dynamiteDance : public playerstate
{
private:
	RECT _rc;
	int _count;
	int _index;
	int _time;
	float _jumpPower;
	float _gravity;
	
public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

