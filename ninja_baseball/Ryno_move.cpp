#include "stdafx.h"
#include "Ryno_move.h"
#include "Ryno_idle.h"
#include "player.h"
#include "Ryno_jump.h"
#include "Ryno_attack.h"
#include "Ryno_crawl.h"
#include "Ryno_damage.h"
playerstate * Ryno_move::handleInput(player * player)
{
	//if (player->isdamage)
	//{
	//	return new Ryno_damage;
	//}
	if (!LEFT&&!RIGHT&&!UP&&!DOWN)
	{

		return new Ryno_idle;
	}
	if (KEYMANAGER->isStayKeyDown('V'))
	{
		return new Ryno_crawl;
	}
	if (KEYMANAGER->isStayKeyDown('C'))
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
	
	if (player->_shadow->getY() < 432)
	{
		player->setY(player->getY() + 432 - player->_shadow->getY());
	}
	if (player->_shadow->getY() + player->_shadow->getHeight() > WINSIZEY)
	{
		player->setY(player->getY() - ((player->_shadow->getY() + player->_shadow->getHeight()) - WINSIZEY));
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		LEFT = true;
		player->isRight = false;
		player->setX(player->getX() - 7);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		RIGHT = true;
		player->isRight = true;
		player->setX(player->getX() + 7);
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		UP = true;
		player->setY(player->getY() - 7);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		DOWN = true;
		player->setY(player->getY() + 7);
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) LEFT = false;
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) RIGHT = false;
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) UP = false;
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) DOWN = false;

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
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth()/2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight()/2);
}

void Ryno_move::enter(player * player)
{
	
	_count = _index =  0;
	 LEFT = RIGHT = UP = DOWN = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_move"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);
	
	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

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

	player->setImageName("Ryno_move");
}
