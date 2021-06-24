#pragma once
#include "playerstate.h"

#define redSpeed 7

class red_jumpState : public playerstate 
{
private:
	RECT _rc;
	int _count;
	int _index;
	float _jumpPower;
	float _grivity;
	bool _isJump;

	float _x; //점프했던 위치를 저장하기 위한 변수
	float _y;

public:
	playerstate* handleInput(player* _player);
	void update(player* _player);
	void enter(player* _player);
};

