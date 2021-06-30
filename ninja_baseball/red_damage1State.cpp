#include "stdafx.h"
#include "red_damage1State.h"
#include "red_idleState.h"
#include "red_standUpState.h"
//#include "red_dieState.h"

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

	if (_player->gethp() == 0) //hp가 0이 되면 red_dieState
	{
		/*return new red_dieState;*/
	}

	return nullptr;
}

void red_damage1State::update(player* _player)
{
	if (_isLie) //바닥에 누우면 _time카운트 증가
	{
		_time++;
	}
		
	//그림자 위치
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	/*_player->_shadow->setY(_player->getY() + 90);*/

	//플레이어가 적에게 맞고 공중에 띄우는고 바닥에 떨어지게 하는것
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

	_player->sethp(_player->gethp() - 1); //에너미한테 맞으면 체력이 1씩 줄어든다
	
	if (_player->gethp() == 0) //플레이어의 hp가 0이 되면
	{
		_player->setlife(_player->getlife() - 1); //플레이어의 라이프가 1씩 줄어든다
	}

	//적에게 맞을떄 공중에 띄우기 위해서 점프값과 중력값 줬음
	_jumpPower = 3.0f;
	_gravity = 0.15f;
	   	
	_count = _index = _time = 0;
	_isLie = false; //적에게 맞고 바닥에 닿았는지

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
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);
}

