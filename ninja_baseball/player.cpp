#include "stdafx.h"
#include "player.h"
#include "red_idleState.h"
#include "red_moveState.h"

HRESULT player::init()
{	
	//_x=
	//_y=
	//idlestate만들면 _state =  new idlestate 해주세요 
	//_state = 
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 + 200;
	_playerrc = RectMakeCenter(_x, _y, 80, 77);
	_state = new red_idleState;
	_state -> enter(this);
	
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
	//이미지랜더
	//_playerimg->frameRender(getMemDC(),)
	_playerimg->frameRender(getMemDC(), _playerrc.left, _playerrc.top, _playerimg->getFrameX(), _playerimg->getFrameY());
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
