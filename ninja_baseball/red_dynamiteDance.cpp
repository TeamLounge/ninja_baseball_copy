#include "stdafx.h"
#include "red_dynamiteDance.h"
#include "red_idleState.h"

playerstate * red_dynamiteDance::handleInput(player * _player)
{
	if (_time > 30)
	{
		_player->setY(_player->getY() + 80);
		return new red_idleState;
	}

	return nullptr;
}

void red_dynamiteDance::update(player * _player)
{
	_count++;

	if (_count % 4 == 0)
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;
		}
		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;
		}

		_count = 0;
	}
	
	if (_index > _player->getImage()->getMaxFrameX())
	{
		_time++;
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setY(_player->getY() + 170);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setY(_player->getY() + 170);
	}
}

void red_dynamiteDance::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_dynamiteDance"));
	_player->setY(_player->getY() - 80);
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_count = _index = _time = 0;
	
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

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5);
		_player->_shadow->setY(_player->getY() + 50);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 50);
	}
}
