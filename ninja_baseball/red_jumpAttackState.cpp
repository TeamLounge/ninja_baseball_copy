#include "stdafx.h"
#include "red_jumpAttackState.h"

playerstate * red_jumpAttackState::handleInput(player * _player)
{
	return nullptr;
}

void red_jumpAttackState::update(player * _player)
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
		}
		if (_player->isRight == false)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
		}
	}
}

void red_jumpAttackState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_jumpAttack"));
	_player->setImageName("red_jumpAttack");

	_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());
	_player->setRect(_rc);

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

	_player->_isRedJumpAttack = true;
}
