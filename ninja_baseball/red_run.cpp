#include "stdafx.h"
#include "red_run.h"
#include "player.h"

playerstate * red_run::handleInput(player * _player)
{
	return nullptr;
}

void red_run::update(player * _player)
{
}

void red_run::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_run"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	_count = _index = 0;

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
}
