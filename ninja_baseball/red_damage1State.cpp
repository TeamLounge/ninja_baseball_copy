#include "stdafx.h"
#include "red_damage1State.h"
#include "red_idleState.h"

playerstate* red_damage1State::handleInput(player* _player)
{
	if (_time > 100)
	{
		return new red_idleState;
	}

	/*if (KEYMANAGER->isOnceKeyDown('Z') && _index > _player->getImage()->getMaxFrameX())
	{
		return new red_standUpState;
	}*/

	return nullptr;
}

void red_damage1State::update(player* _player)
{
	_time++;
	_count++;

	if (_count % 10 == 0)
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

	//그림자 위치
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);
}

void red_damage1State::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage1"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getMaxFrameY());
	_player->setRect(_rc);

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
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);
}

