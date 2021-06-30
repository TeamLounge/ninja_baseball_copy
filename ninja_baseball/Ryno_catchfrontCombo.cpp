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
		if (_count % 3==0)
		{
			_index++;
			if (_index == 2)_Rotation++;
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

	if (_index == 4 || _index==5)
	{
		player->isattack = true;
		if (player->isRight) {
			player->_attack_rc = RectMakeCenter(player->getX() + 90, player->getY(), 50, 50);
		}
		else
		{
			player->_attack_rc = RectMakeCenter(player->getX() - 90, player->getY(), 50, 50);
		}
	}
	else
		player->isattack = false;


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
	_rc = RectMakeCenter(player->getX(), player->getY()+30, 140, 197);
	player->setY(player->_shadow->getY()-90);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	//player->_shadow->setY(player->getY() + 90);

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);

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

	player->setImageName("Ryno_catch_frontCombo");
}
