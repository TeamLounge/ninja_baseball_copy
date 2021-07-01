#include "stdafx.h"
#include "red_gripState.h"
#include "red_idleState.h"
#include "red_legKickState.h"

playerstate* red_gripState::handleInput(player* _player)
{
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new red_legKickState;
	}

	return nullptr;
}

void red_gripState::update(player* _player)
{
	if (KEYMANAGER->isStayKeyDown('Z') && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isMove = true;
		_player->setX(_player->getX() - 6);
	}
	if (KEYMANAGER->isStayKeyDown('Z') && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isMove = true;
		_player->setX(_player->getX() + 6);
	}
	if (KEYMANAGER->isStayKeyDown('Z') && KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_isMove = true;
		_player->setY(_player->getY() - 6);
	}
	if (KEYMANAGER->isStayKeyDown('Z') && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_isMove = true;
		_player->setY(_player->getY() + 6);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_isMove = false;
	}

	_count++;

	if (_isMove)
	{
		if (_count % 8 == 0)
		{
			if (_player->isRight == true)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_index = 0;
				}
			}

			if (_player->isRight == false)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(1);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_index = 0;
				}
			}

			_count = 0;
		}
	}
	
	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	
}

void red_gripState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_grip2"));
	_player->setImageName("red_grip2");
	
	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = 0;
	_isMove = false; //가만히 있을때는 프레임렌더 하지 않기 위해

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
	}
}
