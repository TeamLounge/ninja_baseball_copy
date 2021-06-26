#include "stdafx.h"
#include "Ryno_crawl.h"
#include "Ryno_idle.h"
#include "Ryno_fly.h"
playerstate * Ryno_crawl::handleInput(player * player)
{

	if(KEYMANAGER->isOnceKeyUp('V')) 
	{
		player->setY(player->getY() - 45);
		return new Ryno_idle;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		return new Ryno_fly;
	}
	return nullptr;

}

void Ryno_crawl::update(player * player)
{
	_count++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->isRight = false;
		player->setX(player->getX() - 5);
		if(_count%5==0)
		_index++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->isRight = true;
		player->setX(player->getX() + 5);
		if (_count % 5 == 0)
		_index++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->setY(player->getY() - 5);
		if (_count % 5 == 0)
		_index++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->setY(player->getY() + 5);
		if (_count % 5 == 0)
		_index++;
	}

	if (_index > 4) _index = 0;
	player->getImage()->setFrameX(_index);
	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameY(1);
	}

	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 45);
}

void Ryno_crawl::enter(player * player)
{

	_count = _index = 0;

	player->setImage(IMAGEMANAGER->findImage("Ryno_crawl"));
	player->setY(player->_shadow->getY() - 45);
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY()+45);

	//�¿챸��
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
