#include "stdafx.h"
#include "Ryno_givp_up.h"
#include "Ryno_start.h"
#include "Ryno_fly.h"
playerstate * Ryno_givp_up::handleInput(player * player)
{
	if (_count > 100) {
		if (player->getlife() <= 0)
		{
			player->isEnd = true;
		}
		else
		{

			player->setlife(player->getlife() - 1);
			player->sethp(5);
			return new Ryno_start;
		}
	}
	if (player->isEnd)
	{
		if (KEYMANAGER->isOnceKeyDown())
		{
			return new Ryno_start;
		}
	}
	return nullptr;
}

void Ryno_givp_up::update(player * player)
{
	_count++;
	if (player->getRect().left < CAMERAMANAGER->getCameraLEFT())
	{
		player->setX(player->getX() + CAMERAMANAGER->getCameraLEFT() - player->getRect().left);
	}
}

void Ryno_givp_up::enter(player * player)
{
	image* img = IMAGEMANAGER->findImage("Ryno_give_up");
	_count = 0;
	player->setImage(img);
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setY(player->getY() + 90);
	
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

	player->setImageName("Ryno_give_up");
}
