#include "stdafx.h"
#include "Ryno_catch.h"

playerstate * Ryno_catch::handleInput(player * player)
{
	
	return nullptr;
}

void Ryno_catch::update(player * player)
{

}

void Ryno_catch::enter(player * player)
{
	_count = _index = 0;

	player->setImage(IMAGEMANAGER->findImage("Ryno_catch"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

	//ÁÂ¿ì±¸ºÐ
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
