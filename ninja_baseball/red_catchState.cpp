#include "stdafx.h"
#include "red_catchState.h"
#include "red_idleState.h"
#include "red_catchAttackState.h"
#include "red_throw.h"

playerstate* red_catchState::handleInput(player* _player)
{
	if (_time > 80) //잡은상태에서 일정시간 지나면 ideState로 전환
	{
		_player->iscatch = false;
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z')); //에너미를 잡은 상태에서 때리기
	{
		return new red_catchAttackState;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		return new red_throw; //에너미를 잡고나서 던지기!!(방향키 방향으로??)
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

	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());*/

	if (_player->isRight == true) //오른쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() + 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
	if (_player->isRight == false) //왼쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() - 20, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}

	_player->setRect(_rc);

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

