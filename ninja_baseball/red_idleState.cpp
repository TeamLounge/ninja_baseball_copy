#include "stdafx.h"
#include "red_idleState.h"
#include "red_jumpState.h"
#include "red_moveState.h"
#include "red_attackState.h"
#include "red_idleState2.h"
#include "red_dynamiteDance.h"
//=====================================
#include "red_damage1State.h"
#include "red_damage2State.h"
#include "red_dieState.h"
//=====================================

playerstate * red_idleState::handleInput(player * _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)
		|| KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new red_moveState;
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		return new red_jumpState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_attackState;
	}
	if (_player->isdamage && !_player->invincibility)
	{
		return new red_damage1State;  //에너미에게 맞았을 때
	}
	
	if (_time > 200)
	{
		return new red_idleState2;
	}
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		return new red_dynamiteDance;
	}
	if (_player->gethp() <= 0)
	{
		return new red_dieState;
	}

	//=============================================================================
	//잘 되는지 확인하려고 키설정한 것-> 나중에 삭제할 예정
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		return new red_damage1State; //강하게 공격당했을 때
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		return new red_damage2State; //약하게 공격당했을 때
	}
		

	//if (KEYMANAGER->isOnceKeyDown('K'))
	//{
	//	return new red_dieState; //피가 떨어져서 죽었음
	//}
	//================================================================================

	//if ((KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_UP) && KEYMANAGER->isOnceKeyDown('A')) ||
	//	(KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('A')))
	//{
	//	return new red_attackMotion;
	//}

	return nullptr;
}

void red_idleState::update(player * _player)
{
	_time++; //일정 타임카운터가 쌓이면 idle2로 넘어감 

	if (_player->isRight)
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(0);
	}
	else
	{
		_player->getImage()->setFrameX(0);
		_player->getImage()->setFrameY(1);
	}


	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}

	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);
}

void red_idleState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_idle"));
	_player->setImageName("red_idle");

	_player->sethp(_player->gethp());
	_player->setlife(_player->getlife());
	
	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}

	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
	}
	 	
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	
	if (_player->isRight == true) //오른쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() + 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
	if (_player->isRight == false) //왼쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() - 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
		
	_player->setRect(_rc);

	_count = _index = _time = 0;

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
