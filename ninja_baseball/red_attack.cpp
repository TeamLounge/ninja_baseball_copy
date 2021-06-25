#include "stdafx.h"
#include "red_attack.h"

playerstate * red_attack::handleInput(player * _player)
{
	return nullptr;
}

void red_attack::update(player * _player)
{

}

void red_attack::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_attack"));
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
