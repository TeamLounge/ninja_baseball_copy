#include "stdafx.h"
#include "Ryno_givp_up.h"
#include "Ryno_start.h"
#include "Ryno_fly.h"
playerstate * Ryno_givp_up::handleInput(player * player)
{
	if (_count > 100) {
		if (player->getlife() <= 0)
		{
			return new Ryno_fly;
		}
		else
		{
			player->setlife(player->getlife() - 1);
			player->sethp(5);
			return new Ryno_start;
		}
	}
	return nullptr;
}

void Ryno_givp_up::update(player * player)
{
	_count++;
}

void Ryno_givp_up::enter(player * player)
{
	image* img = IMAGEMANAGER->findImage("Ryno_givp_up");
	_count = 0;
	player->setImage(img);
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
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
