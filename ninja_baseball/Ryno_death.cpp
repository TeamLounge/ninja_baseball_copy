#include "stdafx.h"
#include "Ryno_death.h"
#include "Ryno_givp_up.h"
playerstate * Ryno_death::handleInput(player * player)
{
	if (jumpPower < 0 && player->getY() + (player->getImage()->getFrameHeight() / 2) > player->_shadow->getY())
	{
		player->isdamage = false;
		return new Ryno_givp_up;
	}
	return nullptr;
}

void Ryno_death::update(player * player)
{

	player->setY(player->getY() - jumpPower);
	if (player->isRight)
	{
		player->setX(player->getX() - 2);
	}
	else player->setX(player->getX() + 2);
	jumpPower -= gravity;
	_count++;
	if (player->getRect().left < CAMERAMANAGER->getCameraLEFT())
	{
		player->setX(player->getX() + CAMERAMANAGER->getCameraLEFT() - player->getRect().left);
	}
	if (_count % 3 == 0)
	{
		_index++;
		if (_index > 4) _index = 0;
	}
	player->getImage()->setFrameX(_index);
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
}

void Ryno_death::enter(player * player)
{
	RECT rc;
	image* img = IMAGEMANAGER->findImage("Ryno_death");
	_count = _index = 0;
	jumpPower = 6.f;
	gravity = 0.1f;
	player->setImage(img);
	player->_shadow->setY(player->getY() + 90);

	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);
	if (player->isRight)
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);

		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	}
	else
	{
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) + 15);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);

		player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	}

	player->setImageName("Ryno_death");
}
