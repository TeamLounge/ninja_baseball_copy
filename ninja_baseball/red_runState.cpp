#include "stdafx.h"
#include "red_runState.h"
#include "red_idleState.h"
#include "red_slidingState.h"
#include "red_dashAttackState.h"

playerstate* red_runState::handleInput(player* _player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_slidingState;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new red_dashAttackState;
	}

	return nullptr;
}

void red_runState::update(player* _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->setX(_player->getX() - 12);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->setX(_player->getX() + 12);
	}

	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}

		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5);
		_player->_shadow->setY(_player->getY() + 90);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 90);
	}
}

void red_runState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_run"));

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = 0;
	/*_runTime = 0;*/

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