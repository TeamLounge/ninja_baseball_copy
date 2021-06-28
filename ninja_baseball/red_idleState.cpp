#include "stdafx.h"
#include "red_idleState.h"
#include "red_jumpState.h"
#include "red_moveState.h"
#include "red_attackState.h"
#include "red_idleState2.h"
//=====================================
#include "red_damage1State.h"
#include "red_damage2State.h"
#include "red_downAttackState.h"
//=====================================

playerstate * red_idleState::handleInput(player * _player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)
		|| KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new red_moveState;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new red_jumpState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_attackState;
	}

	if (_time > 200)
	{
		return new red_idleState2;
	}

	//=============================================================================
	//�� �Ǵ��� Ȯ���Ϸ��� Ű������ ��-> ���߿� ������ ����
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		return new red_damage1State; //���ϰ� ���ݴ����� ��
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		return new red_damage2State; //���ϰ� ���ݴ����� ��
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		return new red_downAttackState; //���� ������ �� �������
	}
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
	_time++; //���� Ÿ��ī���Ͱ� ���̸� idle2�� �Ѿ 

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
}

void red_idleState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_idle"));
	
	//�׸��� ��ġ
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 30);
		_player->_shadow->setY(_player->getY() + 90);
	}

	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 30);
		_player->_shadow->setY(_player->getY() + 90);
	}
	
	 	
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	
	_player->setRect(_rc);*/

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
