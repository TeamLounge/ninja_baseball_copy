#include "stdafx.h"
#include "red_dashAttackState.h"
#include "red_idleState.h";

playerstate* red_dashAttackState::handleInput(player* _player)
{
	if (_time == 20)
	{
		return new red_idleState;
	}
	return nullptr;
}

void red_dashAttackState::update(player* _player)
{
	_time++;

	if (_player->isRight == true)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
		if (_time < 20)
		{
			_player->setX(_player->getX() + 25);
		}

		//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
		if (_time < 20)
		{
			_player->isattack = true;
			_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 30, _player->getY(), 70, 70);
		}
		else
		{
			_player->isattack = false;
		}
		//=============================================================

	}
	if (_player->isRight == false)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
		if (_time < 20)
		{
			_player->setX(_player->getX() - 25);
		}

		//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
		if (_time < 20)
		{
			_player->isattack = true;
			_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 30, _player->getY(), 70, 70);
		}
		else
		{
			_player->isattack = false;
		}
		//=============================================================
	}

	//그림자 위치
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);
}

void red_dashAttackState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_dashAttack"));
	_player->setImageName("red_dashAttack");
	
	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

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