#include "stdafx.h"
#include "red_idleState2.h"

playerstate * red_idleState2::handleInput(player * _player)
{
	return nullptr;
}

void red_idleState2::update(player * _player)
{
}

void red_idleState2::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_idle2"));

	//그림자 위치
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	_count = _index = 0;
	
	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(0);
	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(1);
	}
}
