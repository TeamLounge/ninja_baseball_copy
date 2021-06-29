#include "stdafx.h"
#include "Ryno_dashAlt.h"
#include "Ryno_idle.h"
playerstate * Ryno_dashAlt::handleInput(player * player)
{
	if (speed < 0)
	{
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_dashAlt::update(player * player)
{
	if (player->isRight)
	{
		player->setX(player->getX() + speed);
		speed -= inertia;
	}
	else
	{
		player->setX(player->getX() - speed);
		speed -= inertia;
	}
	
	if ( 2.f <speed && speed<11.5f)_index = 1;
	if (speed < 2.f) _index = 2;
	if (_index == 1)
	{
		player->isattack = true;
		if (player->isRight)
			player->_attack_rc = RectMakeCenter(player->getX() + 90, player->getY() - 30, 50, 140);
		else
			player->_attack_rc = RectMakeCenter(player->getX() - 90, player->getY() - 30, 50, 140);
	}
	if (_index == 2)
	{
		player->isattack = false;
	}
	player->getImage()->setFrameX(_index);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
}

void Ryno_dashAlt::enter(player * player)
{
	_count = _index = 0;
	speed = 13.f;
	inertia = 0.2f;
	
	player->setImage(IMAGEMANAGER->findImage("Ryno_dashAttack_alt"));
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
