#include "stdafx.h"
#include "red_homeRunState.h"
#include "red_idleState.h"

playerstate* red_homeRunState::handleInput(player* _player)
{
	if (_index > _player->getImage()->getMaxFrameX())
	{
		_player->setY(_player->getY() + 20);

		if (_player->isRight == true)
		{
			_player->setX(_player->getX() - 60);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() + 60);
		}
		return new red_idleState;
	}

	return nullptr;
}

void red_homeRunState::update(player* _player)
{
	_count++;
	
	if (_count % 5 == 0)
	{
		_index++;

		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_count++;
		}
		
		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_count++;
		}
		
		if (_player->isRight == true)
		{
			if (_count2 < 5 && _index > 3)
			{
				_player->setX(_player->getX() + 50);
			}
		}

		if (_player->isRight == false)
		{
			if (_count2 < 5 && _index > 3)
			{
				_player->setX(_player->getX() - 50);
			}
		}

		//그림자 위치
		if (_player->isRight == true)
		{
			_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 70);
			_player->_shadow->setY(_player->getY() + 110);
		}
		if (_player->isRight == false)
		{
			_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 70);
			_player->_shadow->setY(_player->getY() + 110);
		}
	}
}

void red_homeRunState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_homerun"));
	_player->setImageName("red_homerun");
	
	_player->setY(_player->getY() + 20);
	if (_player->isRight == true)
	{
		_player->setX(_player->getX() + 60);
	}
	if (_player->isRight == false)
	{
		_player->setX(_player->getX() - 60);
	}

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = _count2 = 0;

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