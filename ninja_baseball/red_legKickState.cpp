#include "stdafx.h"
#include "red_legKickState.h"
#include "red_idleState.h"

playerstate * red_legKickState::handleInput(player * _player)
{
	if (_time > 30)
	{
		return new red_idleState;
	}

	return nullptr;
}

void red_legKickState::update(player * _player)
{
	_count++;

	if (_count % 8 == 0)
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

	if (_index > 3 && _index <= _player->getImage()->getMaxFrameX())
	{
		if (_player->isRight == true)
		{
			_player->setX(_player->getX() + 15);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() - 15);
		}

		if (_index > 3 && _index < 7)
		{
			_player->setY(_player->getY() - 3);
		}
		if (_index >= 8  && _index <= _player->getImage()->getMaxFrameX())
		{
			_player->setY(_player->getY() + 3);
		}
				
	}

	if (_player->getImage()->getMaxFrameX() < _index)
	{
		_time++;
	}
	
	//�׸��� ��ġ
	if (_player->isRight == true)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}
	if (_player->isRight == false)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}
}

void red_legKickState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_legKick"));
	_player->setImageName("red_legKick");
	
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	_player->getImage()->getFrameHeight());
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
}
