#include "stdafx.h"
#include "Ryno_attack.h"
#include "Ryno_idle.h"
#include "player.h"
playerstate * Ryno_attack::handleInput(player * player)
{
	
	if (isend)
	{
		return new Ryno_idle;
	}

	return nullptr;
}

void Ryno_attack::update(player * player)
{

	if (_index < 3) {
		_count++;
		if (_count % 3 == 0)
		{
			if(_index<2) _index++;
			if (_count < 30) {
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('Z'))
				{
					player->setImage(IMAGEMANAGER->findImage("Ryno_attack_front"));
					_index = 0;
					_count = 0;
				}
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
				}
			}
			else
				isend = true;
		}
	}
	if(player->getImage() == IMAGEMANAGER->findImage("Ryno_attack_front"))
	{
		_count++;
		if (_count%5==0) {

			if (_index < 5) _index++;
			if (_count < 30) {
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
				}
			}
			if (_index > 6)
			{
				_index++;
				if (_index > 7)
					isend = true;
			}
		}

	}

	if (_index == 3)
	{
		_count++;
		if (_count < 30)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_index++;
				_count = 0;
			}
		}
		else
			isend = true;
	}
	if (_index > 3)
	{
		_count++;
		if (_count % 5 == 0) 
		{
			_index++;
			if (_index > 6)
				isend = true;
		}
	}
	
	player->getImage()->setFrameX(_index);
}

void Ryno_attack::enter(player * player)
{
	RECT rc;
	_count = _index = 0;
	isend = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_attack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

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