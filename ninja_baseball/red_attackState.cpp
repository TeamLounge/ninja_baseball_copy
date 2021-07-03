#include "stdafx.h"
#include "red_attackState.h"
#include "red_idleState.h"
#include "red_homeRunState.h"

playerstate * red_attackState::handleInput(player * _player)
{
	if (_isend)
	{
		_player->setY(_player->getY() + 40);
		_player->_isRedAttack1 = false;
		_player->_isRedAttack2 = false;
		_player->_isRedAttack3 = false;
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new red_homeRunState; //홈런공격
	}
	
	return nullptr;
}

void red_attackState::update(player * _player)
{
	//첫번째 공격
	if (_index < 4 && _attackCount == 0)
	{
		_count++;
		_time++;

		if (_count % 3 == 0)
		{
			if (_index < 3) _index++;

			//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
			if (_index == 1)
			{
				_player->isattack = true;
				_player->_isRedAttack1 = true;

				if (_player->isRight == true)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 50, _player->getY(), 70, 70);
				}
				if (_player->isRight == false)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 50, _player->getY(), 70, 70);
				}
			}
			else
			{
				_player->isattack = false;
			}
			//=============================================================

			if (_time < 30) {

				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_attackCount++;
					_time = 0;
				}
			}

			else
				_isend = true;
		}
	}

	//두번째 공격
	if (_index < 9 && _attackCount == 1)
	{
		_count++;
		_time++;

		if (_count % 2 == 0)
		{
			if (_index < 8) _index++;

			//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
			if (_index == 6)
			{
				_player->isattack = true;
				_player->_isRedAttack2 = true;

				if (_player->isRight == true)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 50, _player->getY(), 70, 70);
				}
				if (_player->isRight == false)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 50, _player->getY(), 70, 70);
				}
			}
			else
			{
				_player->isattack = false;
			}
			//=============================================================

			if (_time < 30)
			{
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_attackCount++;
					_time = 0;
				}
			}

			else
				_isend = true;
		}
	}

	//세번째 공격
	if (_index < 17 && _attackCount == 2)
	{
		_count++;
		_time++;

		if (_count % 2 == 0)
		{
			if (_index < 17) _index++;

			//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
			if (_index == 14)
			{
				_player->isattack = true;
				_player->_isRedAttack3 = true;

				if (_player->isRight == true)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 30, _player->getY() + 40, 70, 70);
				}
				if (_player->isRight == false)
				{
					_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 30, _player->getY() + 40, 70, 70);
				}
			}
			else
			{
				_player->isattack = false;
			}
			//=============================================================

			if (_index == 17)
			{
				_isend = true;
			}
		}
	}

	_player->getImage()->setFrameX(_index);
	
}

void red_attackState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_attack"));
	_player->setImageName("red_attack");

	_player->setY(_player->getY() - 40);
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_count = _index = _time = 0;
	_attackCount = 0;
	_isend = false;
		
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
