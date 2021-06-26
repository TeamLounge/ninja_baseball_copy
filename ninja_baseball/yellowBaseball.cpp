#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"

void yellowBaseball::InputHandle()
{
	ybState* newState = _ybState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_ybState);
		_ybState = newState;
		_ybState->enter(this);
	}
}

HRESULT yellowBaseball::init()
{
	_yellowBaseball.x = 100;
	_yellowBaseball.y = 100;

	_yellowBaseball.img = new image();

	setImage();

	_ybState = new ybMoveState();
	_ybState->enter(this);
	

	return S_OK;
}

void yellowBaseball::release()
{
	_ybState->exit(this);
}

void yellowBaseball::update()
{
	InputHandle();
	_ybState->update(this);
}

void yellowBaseball::render()
{
	_yellowBaseball.img->frameRender(getMemDC(), _yellowBaseball.x, _yellowBaseball.y);
}

void yellowBaseball::setImage()
{
	IMAGEMANAGER->addFrameImage("yBaseball_move", "image/3_Enemy/baseball/yBaseball_move.bmp", 2880, 600, 8, 2, true, RGB(255, 0, 255), false);
}
