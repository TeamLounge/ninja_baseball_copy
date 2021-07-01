#include "stdafx.h"
#include "Ryno_catch.h"
#include "Ryno_idle.h"
#include "Ryno_catchfrontCombo.h"
playerstate * Ryno_catch::handleInput(player * player)
{
	if (isend)
	{
		player->setY(player->getY() + 30);
		player->iscatch = false;
		player->isattack = false;
		player->_isGreenCatchBackAttack = false;
		return new Ryno_idle;
	}
	if (KEYMANAGER->isOnceKeyUp('V'))
	{
		player->setY(player->getY() + 30);
		player->iscatch = false;
		player->isattack = false;
		player->_isGreenCatchBackAttack = false;
		return new Ryno_idle;
	}
	if (isfront)
	{
		
		return new Ryno_catchfrontCombo;
	}


	return nullptr;
}

void Ryno_catch::update(player * player)
{
	if (_index == 0)
	{
		if (player->isRight) {
			player->getImage()->setFrameY(0);
			if (KEYMANAGER->isStayKeyDown(VK_LEFT)&& KEYMANAGER->isOnceKeyDown('Z'))
				_index += 3;
			if(KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('X'))
				isfront = true;
		}
		else
		{
			player->getImage()->setFrameY(1);
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('Z'))
				_index += 3;
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isOnceKeyDown('X'))
				isfront = true;
			if (KEYMANAGER->isOnceKeyDown('Z'))
				_index++;
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
			_index++;
	}
	if (_index > 0 && _index < 3)
	{
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_index == 2)
			{
				player->isattack = true;
				player->_isGreenCatchAttack = true;
				if (player->isRight) {
					player->_attack_rc = RectMakeCenter(player->getX() + 90, player->getY(), 50, 50);
				}
				else
					player->_attack_rc = RectMakeCenter(player->getX() - 90, player->getY(), 50, 50);

			}
			if (_index > 2)
			{ 
				_index = 0;
				player->isattack = false;
			}
			_count = 0;
		}
	}
	if (_index >= 3 && _index <= 5)
	{
		player->_isGreenCatchAttack = false;
		_count++;
		if (_count % 10 == 0)
		{
			if (_index == 3) player->_isGreenCatchBackAttack = true;
			_index++;
			_count = 0;
		}
	}
	if (_index > 5)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 7)
			{
				isend = true;
			}
			_count = 0;
		}

	}
	player->getImage()->setFrameX(_index);
}

void Ryno_catch::enter(player * player)
{
	_count = _index = 0;
	isend = isfront = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_catch"));
	_rc = RectMakeCenter(player->getX(), player->getY()-30, 140, 197);
	player->setY(player->_shadow->getY() - 120);
	player->setRect(_rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

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

	player->setImageName("Ryno_catch");
}
