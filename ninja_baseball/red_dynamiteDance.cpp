#include "stdafx.h"
#include "red_dynamiteDance.h"
#include "red_idleState.h"

playerstate * red_dynamiteDance::handleInput(player * _player)
{
	if (_time > 30)
	{
		_player->setY(_player->getY() + 80);
		_player->isattack = false;
		_player->_isRedDynamiteDance = false;
		return new red_idleState;
	}

	return nullptr;
}

void red_dynamiteDance::update(player * _player)
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

	if (_player->isattack)
	{
		if (_player->isRight)
		{
			_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 30, _player->getY(), 70, 70);
		
		}
		
		else
		{
			_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 30, _player->getY(), 70, 70);
		}
	}
	
	if (_index > _player->getImage()->getMaxFrameX())
	{
		_time++;
	}

	//발차기하고 나서 뒤로 날아가게 하려고
	if (_index >= 30 && _index < _player->getImage()->getMaxFrameX())
	{
		/*_jumpPower = 3.0f;
		_gravity = 0.15;
		_jumpPower -= _gravity;

		_player->setY(_player->getY() - _jumpPower);*/

		_player->_isRedDynamiteDance = false;

		if (_player->isRight == true)
		{
			_player->setX(_player->getX() - 20);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() + 20);
		}
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setY(_player->getY() + 170);
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setY(_player->getY() + 170);
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	}
}

void red_dynamiteDance::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_dynamiteDance"));
	_player->setImageName("red_dynamiteDance");

	_player->setY(_player->getY() - 80);
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_count = _index = _time = 0;
	_jumpPower = 3.0f;
	_gravity = 0.15;

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

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 170 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 170 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}

	_player->isattack = true;
	_player->_isRedDynamiteDance = true;
}
