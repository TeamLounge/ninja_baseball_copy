#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{	
	//_x=
	//_y=
	//idlestate����� _state =  new idlestate ���ּ��� 
	//_state = 
	
	return S_OK;
}

void player::update()
{
	handleInput();
	_state->update(this);
}

void player::release()
{
}

void player::render()
{
	Rectangle(getMemDC(), _playerrc);
	//�̹�������
	//_playerimg->frameRender(getMemDC(),)
}

void player::handleInput()
{
	playerstate* state = _state->handleInput(this);
	if (state != nullptr) 
	{
		SAFE_DELETE(_state);
		_state = state;
		_state->enter(this);
	}
}
