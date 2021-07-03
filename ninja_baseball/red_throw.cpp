#include "stdafx.h"
#include "red_throw.h"
#include "red_idleState.h"

playerstate * red_throw::handleInput(player * _player)
{
	if (_time > 30)
	{
		_player->_isRedThrow = false;
		_player->isattack = false;
		_player->iscatch = false;
		return new red_idleState;
	}

	return nullptr;
}

void red_throw::update(player * _player)
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;
		}

		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;
		}

		_count = 0;
	}

	if (_player->getImage()->getMaxFrameX() < _index)
	{
		_time++;
	}
	
	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
}

void red_throw::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_throw"));
	_player->setImageName("red_throw");

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	_count = _index = _time = 0;

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(1);
	}

	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(0);
	}

	_player->_isRedThrow = true;
}
