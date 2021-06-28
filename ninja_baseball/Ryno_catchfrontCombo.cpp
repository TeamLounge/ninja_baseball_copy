#include "stdafx.h"
#include "Ryno_catchfrontCombo.h"
#include "Ryno_idle.h"
playerstate * Ryno_catchfrontCombo::handleInput(player * player)
{
	if (isend)
	{
		player->iscatch = false;
		return new Ryno_idle;
	}
	return nullptr;
}

void Ryno_catchfrontCombo::update(player * player)
{
	
	if (_index==0)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			_count = 0;
		}
	}
	if (_index > 0 && _index < 3)
	{
		_count++;
		if (_count % 5==0)
		{
			_Rotation++;
			_index++;
			if (_Rotation <= 5)_index = 1;

		}
	}
	if (_index >= 3)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 6) isend = true;
		}
	}

	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameY(1);
	}
	player->getImage()->setFrameX(_index);
}

void Ryno_catchfrontCombo::enter(player * player)
{
	_count = _index = _Rotation = 0;
	isend = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_catch_frontCombo"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setY(player->_shadow->getY() - 120);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	//player->_shadow->setY(player->getY() + 90);

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
