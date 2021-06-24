#include "stdafx.h"
#include "red_attackMotion.h"
#include "player.h"

playerstate * red_attackMotion::handleInpunt(player * _player)
{
	return nullptr;
}

void red_attackMotion::update(player * _player)
{	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->setX(_player->getX() - 8);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->setX(_player->getX() + 8);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->setY(_player->getY() - 8);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->setY(_player->getY() + 8);
	}

	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_index++;

			_player->getImage()->setFrameX(_index++);
			_player->getImage()->setFrameY(0);


		}
		if (_player->isRight == false)
		{
			_index++;

			_player->getImage()->setFrameX(_index++);
			_player->getImage()->setFrameY(1);
		}
	}

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);
}

void red_attackMotion::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_grip2"));
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
