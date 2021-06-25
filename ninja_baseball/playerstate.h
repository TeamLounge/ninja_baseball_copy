#pragma once
#include "player.h"
#include "image.h"

class player;

class playerstate 
{
	//�������� �������̽�
public:
	virtual playerstate* handleInput(player* player) { return nullptr; }
	virtual void update(player* player) {}
	virtual void enter(player* player) {}
};

