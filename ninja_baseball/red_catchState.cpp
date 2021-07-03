#include "stdafx.h"
#include "red_catchState.h"
#include "red_idleState.h"
#include "red_catchAttackState.h"
#include "red_throw.h"
#include "red_gripState.h"
#include "red_homeRunState.h"

playerstate* red_catchState::handleInput(player* _player)
{
	if (_time > 80) //�������¿��� �����ð� ������ ideState�� ��ȯ
	{
		_player->iscatch = false;
		_player->_catchAttackCnt = 0;
		_player->_isRedCatchAttack = false;
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z')) //���ʹ̸� ���� ���¿��� ������
	{
		KEYMANAGER->isOnceKeyUp('Z');
		_player->_catchAttackCnt++;
		if (_player->_catchAttackCnt <= 2)
		{
			return new red_catchAttackState;
		}
	}

	if (_player->isRight)
	{
		if ((KEYMANAGER->isOnceKeyDown(VK_LEFT) && _player->_catchAttackCnt <= 2))
		{
			KEYMANAGER->isOnceKeyUp(VK_LEFT);
			_player->_catchAttackCnt = 0;
			_player->_isRedCatchAttack = false;
			return new red_throw; //���ʹ̸� ����� ������!!(����Ű ��������??)
		}

		if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _player->_catchAttackCnt <= 2))
		{
			KEYMANAGER->isOnceKeyUp(VK_RIGHT);
			_player->_catchAttackCnt = 0;
			_player->_isRedCatchAttack = false;
			return new red_homeRunState; //���ʹ̸� ����� ������!!(����Ű ��������??)
		}
	}

	else
	{
		if ((KEYMANAGER->isOnceKeyDown(VK_LEFT) && _player->_catchAttackCnt <= 2))
		{
			KEYMANAGER->isOnceKeyUp(VK_LEFT);
			_player->_catchAttackCnt = 0;
			_player->_isRedCatchAttack = false;
			return new red_homeRunState; //���ʹ̸� ����� ������!!(����Ű ��������??)
		}

		if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _player->_catchAttackCnt <= 2))
		{
			KEYMANAGER->isOnceKeyUp(VK_RIGHT);
			_player->_catchAttackCnt = 0;
			_player->_isRedCatchAttack = false;
			return new red_throw; //���ʹ̸� ����� ������!!(����Ű ��������??)
		}
	}


	return nullptr;
}

void red_catchState::update(player* _player)
{
	_time++;
}

void red_catchState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_grip2"));
	_player->setImageName("red_grip2");

	//�׸��� ��ġ
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

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());

	if (_player->isRight == true) //�����ʹ����϶� ��Ʈ����
	{
		_rc = RectMakeCenter(_player->getX() + 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
	if (_player->isRight == false) //���ʹ����϶� ��Ʈ����
	{
		_rc = RectMakeCenter(_player->getX() - 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}

	_player->setRect(_rc);

	if (_player->_catchAttackCnt > 0)
	{
		_time = 40;
	}
	else _time = 0;


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

