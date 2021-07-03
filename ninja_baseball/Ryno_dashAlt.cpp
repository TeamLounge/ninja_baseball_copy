#include "stdafx.h"
#include "Ryno_dashAlt.h"
#include "Ryno_idle.h"
#include "Ryno_damage.h"
playerstate * Ryno_dashAlt::handleInput(player * player)
{
	if (speed < 0)
	{
		player->_isGreenDashAlt = false;
		return new Ryno_idle;
	}
	if (player->isdamage && !player->invincibility)
	{
		player->sethp(player->gethp() - 1);
		return new Ryno_damage;
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
		player->_isGreenDashAlt = true;
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
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
}

void Ryno_dashAlt::enter(player * player)
{
	_count = _index = 0;
	speed = 13.f;
	inertia = 0.2f;
	
	player->setImage(IMAGEMANAGER->findImage("Ryno_dashAttack_alt"));
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
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

	player->setImageName("Ryno_dashAttack_alt");
}
