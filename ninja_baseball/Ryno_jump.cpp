#include "stdafx.h"
#include "Ryno_jump.h"
#include "player.h"
#include "Ryno_idle.h"

playerstate * Ryno_jump::handleInput(player * player)
{
	if (_jumpPower < -10)
	{
		return new Ryno_idle; 
	} 
 	return nullptr;
}

void Ryno_jump::update(player * player)
{

	//_count++;

	player->setY(player->getY() - _jumpPower);
	_jumpPower -= _gravity;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - 5);
		player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + 5);
		player->isRight = true;
	}

	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameY(1);
	}

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	//player->_shadow->setY(player->getY() + 90  + _jumpPower);
}

void Ryno_jump::enter(player * player)
{
	RECT rc;
	_count = _index = 0;
	_jumpPower = 10.0f;
	_gravity = 0.2f;

	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90 );


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
