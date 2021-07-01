#include "stdafx.h"
#include "red_fallState.h"
#include "red_idleState.h"

playerstate * red_fallState::handleInput(player * _player)
{
	if (_player->getY() + _player->getImage()->getFrameHeight() / 2 >= _player->_shadow->getY())
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

	return nullptr;
}

void red_fallState::update(player * _player)
{
	_jumpPower -= _gravity;
	_player->setY(_player->getY() - _jumpPower);

	//그림자 위치
	if (_player->isRight == true)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2));*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}

	if (_player->isRight == false)
	{
		/*_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2));*/
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	}
}

void red_fallState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_jump"));
	_player->setImageName("red_jump");

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

	_jumpPower = 0;
	_gravity = 0.5f;
	
	_index = 0;

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
