#include "stdafx.h"
#include "red_damage2State.h"
#include "red_idleState.h"

playerstate* red_damage2State::handleInput(player* _player)
{
	if (_time > 30)
	{
		return new red_idleState;
	}

	return nullptr;
}

void red_damage2State::update(player* _player)
{
	_time++;
}

void red_damage2State::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage2"));
	_player->setImageName("red_damage2");

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getMaxFrameY());
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

	//그림자 위치
	_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
	_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
}
