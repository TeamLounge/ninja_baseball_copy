#include "stdafx.h"
#include "red_standUpState.h"
#include "red_idleState.h"

playerstate* red_standUpState::handleInput(player* _player)
{
	if (_time > 15)
	{
		_player->setY(_player->getY() + 30);
		return new red_idleState;
	}

	return nullptr;
}

void red_standUpState::update(player* _player)
{
	_count++;

	if (_count % 4 == 0)
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;
		}

		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;
		}
		_count = 0;
	}

	//에너미와 충돌할 렉트 생성
	if (_index == 5)
	{
		_player->isattack = true;

		if (_player->isRight == true)
		{
			_player->_attack_rc = RectMakeCenter(_player->getX(), _player->getY() - 20, 300, 80);
		}
		if (_player->isRight == false)
		{
			_player->_attack_rc = RectMakeCenter(_player->getX(), _player->getY() - 20, 300, 80);
		}
	}
	else
	{
		_player->isattack = false;
	}

	if (_index > _player->getImage()->getMaxFrameX())
	{
		_time++;
	}

	//그림자 위치
	/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 15);
	_player->_shadow->setY(_player->getY() + 120);*/
	_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	_player->setShadowY(_player->getY() + 120 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
}

void red_standUpState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_standUp"));
	_player->setImageName("red_standUp");

	_player->setY(_player->getY() - 120);
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	
	/*_player->setRect(_rc);*/

	_count = _index = _time = 0;

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