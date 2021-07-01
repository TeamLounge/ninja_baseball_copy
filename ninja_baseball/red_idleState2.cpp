#include "stdafx.h"
#include "red_idleState2.h"
#include "red_idleState.h"
#include "red_moveState.h"
#include "red_jumpState.h"

playerstate * red_idleState2::handleInput(player * _player)
{
	if (_rotation > 4)
	{
		return new red_idleState;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT) ||
		KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new red_moveState;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new red_jumpState;
	}

	return nullptr;
}

void red_idleState2::update(player * _player)
{
	_count++;

	if (_count % 10 == 0)
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;

			if (_player->getImage()->getMaxFrameX() < _index)
			{
				_index = 0;
				_rotation++;
			}
			_count = 0;
		}


		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;

			if (_player->getImage()->getMaxFrameX() < _index)
			{
				_index = 0;
				_rotation++;
			}
			_count = 0;
		}
		
	}
}

void red_idleState2::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_idle2"));
	_player->setImageName("red_idle2");

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 5);
		_player->_shadow->setY(_player->getY() + 90);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 90);
	}
	
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_count = _index = _rotation = 0;
	
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
