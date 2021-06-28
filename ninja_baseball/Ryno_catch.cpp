#include "stdafx.h"
#include "Ryno_catch.h"
#include "Ryno_idle.h"
playerstate * Ryno_catch::handleInput(player * player)
{
	if (KEYMANAGER->isOnceKeyUp('V'))
	{
		player->setY(player->getY() + 30);
		player->iscatch = false;
		return new Ryno_idle;
	}
	if (isend)
	{
		player->setY(player->getY() + 30);
		player->iscatch = false;
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_catch::update(player * player)
{
	if (_index == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (player->isRight)
				player->getImage()->setFrameY(0);
			else
				player->getImage()->setFrameY(1);
			if (KEYMANAGER->isOnceKeyDown('Z'))
				_index += 3;
		}
		else if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_index++;
		}
	}
	if (_index > 0 && _index < 3)
	{
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 2) _index = 0;
			_count = 0;
		}
	}
	if (_index > 2)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 5) isend = true;
			_count = 0;
		}
	}
	player->getImage()->setFrameX(_index);
}

void Ryno_catch::enter(player * player)
{
	_count = _index = 0;

	player->setImage(IMAGEMANAGER->findImage("Ryno_catch"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setY(player->_shadow->getY() - 120);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	//player->_shadow->setY(player->getY() + 90);

	//ÁÂ¿ì±¸ºÐ
	if (player->isRight)
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}
}
