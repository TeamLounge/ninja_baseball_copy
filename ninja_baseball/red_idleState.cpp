#include "stdafx.h"
#include "red_idleState.h"
#include "red_jumpState.h"
#include "red_moveState.h"
#include "red_attackState.h"
#include "red_idleState2.h"

playerstate * red_idleState::handleInput(player * _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)
		|| KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new red_moveState;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		return new red_jumpState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_attackState;
	}

	if (_time > 200)
	{
		return new red_idleState2;
	}

	//if ((KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_UP) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('A')))
	//{
	//	return new red_attackMotion;
	//}

	return nullptr;
}

void red_idleState::update(player * _player)
{
	_time++;
	/*_time++;
	if (_time >= 150)
	{
		if (_Rotation < 4)
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
	}*/


	if (_player->isRight)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
	else
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
	}
}

void red_idleState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_idle"));
	
	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 30);
		_player->_shadow->setY(_player->getY() + 90);
	}

	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 30);
		_player->_shadow->setY(_player->getY() + 90);
	}
	
	 	
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	
	_player->setRect(_rc);

	_count = _index = 0;

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(0);
	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(_index);
		_player->getImage()->setFrameY(1);
	}


}
