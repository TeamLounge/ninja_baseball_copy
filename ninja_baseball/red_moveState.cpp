#include "stdafx.h"
#include "red_moveState.h"
#include "red_idleState.h"
#include "red_jumpState.h"
#include "red_attack.h"

playerstate * red_moveState::handleInput(player * _player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //มกวม
	{
		return new red_jumpState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_attack;
	}

	return nullptr;
}

void red_moveState::update(player * _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getX() > 0)
	{
		_player->setX(_player->getX() - redSpeed);
		_player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getX() < WINSIZEX)
	{
		_player->setX(_player->getX() + redSpeed);
		_player->isRight = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getY() > 0)
	{
		_player->setY(_player->getY() - redSpeed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->getY() < WINSIZEY)
	{
		_player->setY(_player->getY() + redSpeed);
	}

	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}
		if (_player->isRight == false)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}
	}

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

}

void red_moveState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_walk"));
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
		_player->getImage()->setFrameY(1);
	}

}
