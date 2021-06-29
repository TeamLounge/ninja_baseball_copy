#include "stdafx.h"
#include "red_jumpState.h"
#include "red_idleState.h"
#include "red_jumpAttackState.h"

playerstate * red_jumpState::handleInput(player * _player)
{
	if (_player->getY() + 90 >= _player->_shadow->getY())
	{
		if (_player->isRight == true)
		{
			_player->setX(_player->getX());
		}

		if (_player->isRight == false)
		{
			_player->setX(_player->getX());
		}
		
		return new red_idleState;
	}

	/*if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_jumpAttackState;
	}*/

	return nullptr;
}

void red_jumpState::update(player * _player)
{
	_jumpPower -= _grivity;
	_player->setY(_player->getY() - _jumpPower);

	/*_rc = RectMakeCenter(_player->getX() , _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) //점프중 왼쪽 이동
	{
		_player->setX(_player->getX() - redSpeed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) //점프중 오른쪽 이동
	{
		_player->setX(_player->getX() + redSpeed);
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2));
		
	}

	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2));
		
	}

	//점프 공격
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_isJumpAttack = true;
	}

	if (_isJumpAttack)
	{
		_count++;

		if (_count % 4 == 0)
		{
			_player->setImage(IMAGEMANAGER->findImage("red_jumpAttack"));

			if (_player->isRight == true)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
				
				//점프 공격시 에너미와 충돌할 렉트 생성(오른쪽을 바라볼 때)
				if (_index == 0)
				{
					_player->isattack = true;
					_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 30, _player->getY() + 120, 70, 70);
				}
				else
				{
					_player->isattack = false;
				}

				_index++;
			}

			if (_player->isRight == false)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(1);

				//점프 공격시 에너미와 충돌할 렉트 생성(왼쪽을 바라볼 때)
				if (_index == 0)
				{
					_player->isattack = true;
					_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 30, _player->getY() + 120, 70, 70);
				}
				else
				{
					_player->isattack = false;
				}

				_index++;
			}
			
			_count = 0;
		}
	}
		
}

void red_jumpState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_jump"));
	if (_player->isRight == true)
	{
		_player->setX(_player->getX());
	}
	if (_player->isRight == false)
	{
		_player->setX(_player->getX());
	}
	
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);*/

	_jumpPower = 13.0f;
	_grivity = 0.5f;
	_isJumpAttack = false;
	
	_count = _index = 0;

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
