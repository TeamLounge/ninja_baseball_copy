#include "stdafx.h"
#include "Ryno_dashAttack.h"
#include "Ryno_idle.h"
playerstate * Ryno_dashAttack::handleInput(player * player)
{
	if (speed < 0)
	{
		player->isattack = false;
		player->_isGreenDashAttack = false;
		player->setY(player->getY() - 30);
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_dashAttack::update(player * player)
{
	if (player->isRight) 
	{
		player->setX(player->getX()+speed);
		speed -= inertia;
	}
	else
	{
		player->setX(player->getX() - speed);
		speed -= inertia;
	}

	player->isattack = true;
	player->_isGreenDashAttack = true;
	if(player->isRight)
		player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY() - 40, 50, 80);
	else
		player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY() - 40, 50, 80);
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
}

void Ryno_dashAttack::enter(player * player)
{
	_count = _index = 0;
	speed = 10.f;
	inertia = 0.2f;
	player->setImage(IMAGEMANAGER->findImage("Ryno_dashAttack_ctrl"));
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);
	player->setY(player->_shadow->getY() - 60);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 60);

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 60 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

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

	player->setImageName("Ryno_dashAttack_ctrl");
}
