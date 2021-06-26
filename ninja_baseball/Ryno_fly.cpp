#include "stdafx.h"
#include "Ryno_fly.h"
#include "Ryno_jump.h"

playerstate * Ryno_fly::handleInput(player * player)
{
	if (isend)
	{
		return new Ryno_jump;
	}
	return nullptr;
}

void Ryno_fly::update(player * player)
{

	if (_index < 2)
	{
		_count++;
		_commandTime++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 1) _index = 0;
			if (_commandTime < 50)
			{
				if (KEYMANAGER->isOnceKeyDown('X'))
				{
					isattack = true;
				}
			}
			else if (_commandTime > 50 && !next)
				isend = true;
			_count = 0;

		}
		if (player->getY() >= _top)
		{
			player->setY(player->getY() - 10);
			player->setX(player->getX() - 2);
		}
	}

	if (_index<2 && isattack)
	{
		_actiontime++;
		next = true;
		player->_attack_rc = RectMakeCenter(player->getX() + cosf(0.75)*_top, player->getX() + sinf(0.75)*_top, 100, 100);
		if (_actiontime > 100)
		{
			_index++;
			_actiontime = 0;
			_commandTime = 0;
			_count = 0;
		}
	}


	if (_index == 2)
	{
		if (player->getY()+(player->getImage()->getFrameHeight()/2) < player->_shadow->getY())
		{
			player->setX(player->getX() + 2);
			player->setY(player->getY() + 10);
		}
		else
		{
			_index++;
		}
	}



	if (_index == 3)
	{
		_actiontime++;
		if (_actiontime < 10)
		{
			player->setX(player->getX() + 2);
			player->setY(player->getY() - 5);
		}
		else
			isend = true;
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

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
}

void Ryno_fly::enter(player * player)
{
	_count = _index = 0;
	_actiontime = _commandTime =  0;

	_jumpPower = 10.0f;
	_gravity = 0.2f;
	next = false;
	isattack = false;
	isend = false;
	//플레이어의 이미지,렉트,그림자 초기화
	player->setImage(IMAGEMANAGER->findImage("Ryno_fly"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	//player->_shadow->setY(player->getY() + 90);
	_top = player->_shadow->getY()-300;
	//좌우구분
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
