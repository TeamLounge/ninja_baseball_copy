#include "stdafx.h"
#include "red_dynamiteDance.h"

playerstate * red_dynamiteDance::handleInput(player * _player)
{
	return nullptr;
}

void red_dynamiteDance::update(player * _player)
{
}

void red_dynamiteDance::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_attack"));
	_player->setY(_player->getY() - 40);
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_count = _index = _time = 0;
	_attackCount = 0;
	_isend = false;

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
