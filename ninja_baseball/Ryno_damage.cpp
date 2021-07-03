#include "stdafx.h"
#include "Ryno_damage.h"
#include "Ryno_idle.h"
#include "Ryno_death.h"
#include "Ryno_fall.h"
playerstate * Ryno_damage::handleInput(player * player)
{
	if (player->gethp() <= 0)
	{
		return new Ryno_death;
	}
	if (isend)
	{
		player->isdamage = false;
		player->invincibility = true;
		if (player->getY() + player->getImage()->getHeight() < player->getShadowY())
		{
			return new Ryno_fall;
		}
		return new Ryno_idle;
	}
	
	return nullptr;
}

void Ryno_damage::update(player * player)
{
	_time++;
	if (_time < 30)
	{
		if (player->isRight)
		{
			player->setX(player->getX() - 5);
		}
		else
			player->setX(player->getX() + 5);
	}
	else isend = true;

	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);

	player->_shadow->setY(player->getY() + 90);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);
	
	if (player->isRight)
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	}
	else
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) + 15);
		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	}
}

void Ryno_damage::enter(player * player)
{
	image* img = IMAGEMANAGER->findImage("Ryno_damage");
	_time = 0;
	isend = false;
	player->setImage(img);
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
	player->_shadow->setY(player->getY() + 90);

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);
	if (player->isRight)
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) + 15);
		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}

	player->setImageName("Ryno_damage");
}
