#include "stdafx.h"
#include "Ryno_start.h"
#include "Ryno_idle.h"
playerstate * Ryno_start::handleInput(player * player)
{
	if (_count > 30)
	{
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_start::update(player * player)
{
	_count++;
}

void Ryno_start::enter(player * player)
{
	image* img = IMAGEMANAGER->findImage("Ryno_start");
	_count = 0;
	player->setImage(img);
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2) - 15);
	player->_shadow->setY(player->getY() + 90);

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

	player->getImage()->setFrameX(0);
	player->getImage()->setFrameY(0);

	player->setImageName("Ryno_start");
}
