#include "stdafx.h"
#include "red_runState.h"
#include "red_idleState.h"
#include "red_slidingState.h"
#include "red_dashAttackState.h"
#include "red_damage1State.h"

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

	if (_player->isdamage)
	{
		return new red_damage1State;
	}

	return nullptr;
}

void red_runState::update(player* _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->setX(_player->getX() - 8);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->setX(_player->getX() + 8);
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
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) -15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}

	if (_player->isRight == true) //오른쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() + 10, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
	if (_player->isRight == false) //왼쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() - 10, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}

	_player->setRect(_rc);

}

void red_runState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_run"));
	_player->setImageName("red_run");

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

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