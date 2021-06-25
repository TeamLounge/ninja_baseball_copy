#include "stdafx.h"
#include "redShadow.h"


HRESULT redShadow::init()
{
	_player = new player;
	_player->init();

	_x = _player->getX();
	_y = _player->getY();
	_shadowImage = IMAGEMANAGER->findImage("shadow");
	_rc = RectMakeCenter(_x, _y, _shadowImage->getWidth(), _shadowImage->getHeight());

	return S_OK;
}

void redShadow::release()
{
}

void redShadow::update()
{
	_x = _player->getX();
	_y = _player->getY();
	_rc = RectMakeCenter(_x, _y, _shadowImage->getWidth(), _shadowImage->getHeight());
}

void redShadow::render()
{ 
	_shadowImage->render(getMemDC(), _rc.left, _rc.right);
}
