#include "stdafx.h"
#include "red_dieState.h"
#include "red_startState.h"

playerstate * red_dieState::handleInput(player * _player)
{
	if (_time > 230)
	{
		if (_player->getlife() <= 0)
		{
			_player->isEnd = true;
		}
		else
		{
			_player->sethp(5);
			return new red_startState;
		}
	}
	return nullptr;
}

void red_dieState::update(player * _player)
{
	_time++;
	
	if (_rotation < 7)
	{
		_count++;

		if (_count % 6 == 0)
		{
			if (_player->isRight == true)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_rotation++;
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
					_rotation++;
					_index = 0;
				}
			}

			_count = 0;
		}
	}
	
	else // 4번 돌고나서 플레이어가 쓰러진 이미지
	{
		_player->setImage(IMAGEMANAGER->findImage("red_die"));
		_player->setImageName("red_die");

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
	
	if (!_isLie)
	{
		_jumpPower -= _gravity;
		_player->setY(_player->getY() - _jumpPower);

		if (_player->isRight == true)
		{
			_player->setX(_player->getX() - 2);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() + 2);
		}
	}
	
	if (_time > 125) //일단 일정시간이 지나면 눕는상태로 했음
	{
		_isLie = true;
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}

	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);
}

void red_dieState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage3"));
	_player->setImageName("red_damage3");

	//죽으면 life 1개 줄어든다
	_player->setlife(_player->getlife() - 1);
	if (_player->getlife() <= 0)
	{
		_player->setlife(0);
	}


	_count = _index = _time = 0;
	_rotation = 0;
	_jumpPower = 12.5f;
	_gravity = 0.2f;
	_isLie = false; //바닥에 닿았는지 확인
	
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
