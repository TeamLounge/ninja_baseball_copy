#include "stdafx.h"
#include "Ryno_dash.h"
#include "Ryno_idle.h"
playerstate * Ryno_dash::handleInput(player * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		return new Ryno_idle;
	}

	return nullptr;
}

void Ryno_dash::update(player * player)
{
	_count++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->isRight = false;
		player->setX(player->getX() - 8);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->isRight = true;
		player->setX(player->getX() + 8);

	}

	if (_count % 5 == 0)
	{
		if (_index > 6) _index = 0;
		player->getImage()->setFrameX(_index);
		if (player->isRight)
		{
			player->getImage()->setFrameY(0);
		}
		else
		{
			player->getImage()->setFrameY(1);
		}
		_index++;
		_count = 0;
	}
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);
}

void Ryno_dash::enter(player * player)
{
	_count = _index = 0;
	player->setImage(IMAGEMANAGER->findImage("Ryno_dash"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

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
