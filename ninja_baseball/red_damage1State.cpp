#include "stdafx.h"
#include "red_damage1State.h"
#include "red_idleState.h"
#include "red_standUpState.h"

playerstate* red_damage1State::handleInput(player* _player)
{
	if (_time > 50)
	{
		_player->isdamage = false;
		_player->setY(_player->getY() - 90);
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z') && _isLie)
	{
		_player->isdamage = false;
		return new red_standUpState;
	}

	return nullptr;
}

void red_damage1State::update(player* _player)
{
	if (_isLie) //�ٴڿ� ����� _timeī��Ʈ ����
	{
		_time++;
	}
		
	//�׸��� ��ġ
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	/*_player->_shadow->setY(_player->getY() + 90);*/

	//�÷��̾ ������ �°� ���߿� ���°� �ٴڿ� �������� �ϴ°�
	_jumpPower -= _gravity;
	_player->setY(_player->getY() - _jumpPower);

	if (_player->isRight == true)
	{
		if (!_isLie)
		{
			_player->getImage()->setFrameX(0);
			_player->getImage()->setFrameY(0);
			_player->setX(_player->getX() - 5);
		}
		else
		{
			_player->getImage()->setFrameX(1);
			_player->getImage()->setFrameY(0);
		}
	}
	if (_player->isRight == false)
	{
		if (!_isLie)
		{
			_player->getImage()->setFrameX(0);
			_player->getImage()->setFrameY(1);
			_player->setX(_player->getX() + 5);
		}
		else
		{
			_player->getImage()->setFrameX(1);
			_player->getImage()->setFrameY(1);
		}
	}

	if (_player->getY() >= _player->_shadow->getY())
	{
		_player->setY(_player->_shadow->getY());
		_isLie = true;
	}
}

void red_damage1State::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage1"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getMaxFrameY());
	_player->setRect(_rc);

	//������ ������ ���߿� ���� ���ؼ� �������� �߷°� ����
	_jumpPower = 3.0f;
	_gravity = 0.15f;
	   	
	_count = _index = _time = 0;
	_isLie = false; //������ �°� �ٴڿ� ��Ҵ��� 

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

	//�׸��� ��ġ
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);
}

