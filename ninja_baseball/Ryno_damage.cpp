#include "stdafx.h"
#include "Ryno_damage.h"
#include "Ryno_idle.h"
playerstate * Ryno_damage::handleInput(player * player)
{
	if (isend)
	{
		player->isdamage = false;
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
}

void Ryno_damage::enter(player * player)
{
	RECT rc;
	image* img = IMAGEMANAGER->findImage("Ryno_damage");
	_time = 0;
	isend = false;
	player->setImage(img);
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
	player->_shadow->setY(player->getY() + 90);
	if (player->isRight)
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) + 15);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}
}
