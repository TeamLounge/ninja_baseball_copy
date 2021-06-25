#include "stdafx.h"
#include "red_jumpState.h"
#include "red_idleState.h"
#include "red_jumpAttackState.h"

playerstate * red_jumpState::handleInput(player * _player)
{
	if (_player->getY() >= _player->getImage()->getY())
	{
		/*_player->setY(_y);*/
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new red_jumpAttackState;
	}

	return nullptr;
}

void red_jumpState::update(player * _player)
{
	_jumpPower -= _grivity;
	_player->setY(_player->getY() - _jumpPower);

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) //점프중 왼쪽 이동
	{
		_player->setX(_player->getX() - redSpeed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) //점프중 오른쪽 이동
	{
		_player->setX(_player->getX() + redSpeed);
	}
}

void red_jumpState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_jump"));
	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

	_jumpPower = 16.0f;
	_grivity = 0.5f;

	_x = _player->getX(); //점프했던 위치를 담음
	_y = _player->getY();

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
