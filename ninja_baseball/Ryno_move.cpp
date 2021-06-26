#include "stdafx.h"
#include "Ryno_move.h"
#include "Ryno_idle.h"
#include "player.h"
#include "Ryno_jump.h"
#include "Ryno_attack.h"
#include "Ryno_crawl.h"

playerstate * Ryno_move::handleInput(player * player)
{

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) ||
		KEYMANAGER->isOnceKeyUp(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyUp(VK_UP) ||
		KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{

		return new Ryno_idle;
	}
	if (KEYMANAGER->isStayKeyDown('V'))
	{
		return new Ryno_crawl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		return new Ryno_jump;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new Ryno_attack;
	}
	return nullptr;
}

void Ryno_move::update(player * player)
{
	_count++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->isRight = false;
		player->setX(player->getX() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->isRight = true;
		player->setX(player->getX() + 5);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->setY(player->getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->setY(player->getY() + 5);
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

void Ryno_move::enter(player * player)
{
	
	_count = _index =  0;
	player->setImage(IMAGEMANAGER->findImage("Ryno_move"));
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
