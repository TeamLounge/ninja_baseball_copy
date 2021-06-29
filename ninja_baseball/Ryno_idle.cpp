#include "stdafx.h"
#include "Ryno_idle.h"
#include "player.h"
#include "Ryno_move.h"
#include "Ryno_jump.h"
#include "Ryno_attack.h"
#include "Ryno_crawl.h"
#include "Ryno_dash.h"
#include "Ryno_damage.h"
#include "enemyManager.h"
playerstate * Ryno_idle::handleInput(player * player)
{

	if (player->isdamage)
	{
		player->sethp(player->gethp() - 1);
		return new Ryno_damage;
	}
	if (KEYMANAGER->isStayKeyDown('V'))
	{
		return new Ryno_crawl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		
		player->_isrun = true;
		if (player->_run)
		{
			player->_run = false;
			player->_isrun = false;
			return new Ryno_dash;
		}
		return new Ryno_move;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{

		player->_isrun = true;
		if (player->_run)
		{
			player->_run = false;
			player->_isrun = false;
			return new Ryno_dash;
		}
		return new Ryno_move;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)||KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new Ryno_move;
	}
	if (KEYMANAGER->isStayKeyDown('C'))
	{
		return new Ryno_jump;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new Ryno_attack;
	}
	return nullptr;
}

void Ryno_idle::update(player * player)
{

	_time++;
	if (_time >= 150 )
	{
		
		if (_Rotation<4)
		{
			_count++;
			if (_count % 2 == 0) {
				_index++;
				player->getImage()->setFrameX(_index);
				if (_index > 4)
				{
					_index = 0;
					_Rotation++;
				}
				_count = 0;
			}
		}
		else
		{
			_count++;
			if (_count % 7 == 0) {
				_index++;
				player->getImage()->setFrameX(_index);
				if (_index > 4)
				{
					_index = 0;
					player->getImage()->setFrameX(_index);
					_Rotation = 0;
					_time = 0;
				}
				_count = 0;
			}
		}
	}
}

void Ryno_idle::enter(player * player)
{
	RECT rc;
	image* img = IMAGEMANAGER->findImage("Ryno_idle");
	_count = _index = _time = _Rotation= 0;
	player->setImage(img);
	rc = RectMakeCenter(player->getX(), player->getY(), 140 , 197);
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
		player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2)+15);
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}
}
