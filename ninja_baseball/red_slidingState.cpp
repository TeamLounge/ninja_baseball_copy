#include "stdafx.h"
#include "red_slidingState.h"
#include "red_idleState.h"

playerstate* red_slidingState::handleInput(player* _player)
{
	if (_time == 50)
	{
		_player->setY(_player->getY() - 40);
		_player->_isRedSliding = false;
		return new red_idleState;
	}

	return nullptr;
}

void red_slidingState::update(player* _player)
{
	_time++;

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
		if (_time < 50)
		{
			_player->setX(_player->getX() + 15);
		
			if (_time < 45) //슬라이딩 공격할때 에너미와 충돌할 렉트 생성
			{
				_player->isattack = true;
				_player->_isRedSliding = true;
				_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 30, _player->getY() + 50, 80, 80);
			}
			else
			{
				_player->isattack = false;
			}
		}

		

	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
		if (_time < 50)
		{
			_player->setX(_player->getX() - 15);

			if (_time < 45) //슬라이딩 공격할때 에너미와 충돌할 렉트 생성
			{
				_player->isattack = true;
				_player->_isRedSliding = true;
				_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 30, _player->getY() + 50, 80, 80);
			}
			else
			{
				_player->isattack = false;
			}
		}
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 50 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 50 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);
}

void red_slidingState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_sliding"));
	_player->setImageName("red_sliding");

	_player->setY(_player->getY() + 40);
		

	_time = 0;

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