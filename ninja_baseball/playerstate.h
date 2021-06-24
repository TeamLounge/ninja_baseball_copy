#pragma once

class player;

class playerstate 
{
	//상태패턴 인터페이스
public:
	virtual playerstate* handleInput(player* player) { return nullptr; }
	virtual void update(player* player) {}
	virtual void enter(player* player) {}
};

