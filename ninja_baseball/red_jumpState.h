#pragma once
#include "playerstate.h"

#define redSpeed 7

class red_jumpState :  public playerstate
{
private:
	RECT _rc;
	int _count;
	int _index;
	float _jumpPower;
	float _grivity;
	bool _isJump;
	bool _isJumpAttack;
		
	float _y;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

