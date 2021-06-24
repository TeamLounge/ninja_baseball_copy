#include "stdafx.h"
#include "red_attck.h"
#include "player.h"
#include "red_idleState.h"
#include "red_moveState.h"

playerstate * red_attck::handleInpunt(player * _player)
{
	if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
	{
		_startIndex = 0;

		return new red_idleState;
	}

	return nullptr;
}

void red_attck::update(player * _player)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_attackCount == 0)
		{
			_startIndex = 0;
		}
	}
	
	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_startIndex++;

			_player->getImage()->setFrameX(_startIndex++);
			_player->getImage()->setFrameY(0);
	

		}
		if (_player->isRight == false)
		{
			_startIndex++;

			_player->getImage()->setFrameX(_startIndex++);
			_player->getImage()->setFrameY(1);
		}
	}
		
}

void red_attck::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_attack"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);
	
	_attackCount = 0;
	_count = _startIndex = _endIndex = 0;

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
