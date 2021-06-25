#include "stdafx.h"
#include "red_attackState.h"
#include "red_idleState.h"

playerstate * red_attackState::handleInput(player * _player)
{
	if (KEYMANAGER->isOnceKeyUp('Z')/* && _attackCount > 100*/)
	{
		_attackCount = 0;
		return new red_idleState;
	}
	return nullptr;
}

void red_attackState::update(player * _player)
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_index = 0;
	}

	_count++;
	
	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_index++;
			_attackCount++;
			if (_index < 3)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
			}
		}
		if (_player->isRight == false)
		{
			_index++;
			_attackCount++;
			if (_index < 3)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(1);
			}
		}

			_count = 0;
	}
}

void red_attackState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_attack"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	_count = _index = 0;
	_attackCount = 0;

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
