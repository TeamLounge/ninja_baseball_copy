#include "stdafx.h"
#include "red_homeRunState.h"
#include "red_idleState.h"

playerstate* red_homeRunState::handleInput(player* _player)
{
	if (_index > _player->getImage()->getMaxFrameX())
	{
		return new red_idleState;
	}

	return nullptr;
}

void red_homeRunState::update(player* _player)
{
	_count++;


	if (_count % 4 == 0)
	{
		_index++;

		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_count++;

			if (_count2 < 5 && _index > 1)
			{
				_player->setX(_player->getX() + 30);
			}
		}

		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_count++;

			if (_count2 < 5 && _index > 1)
			{
				_player->setX(_player->getX() - 30);
			}
		}

		//�׸��� ��ġ
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 90);

	}
}

void red_homeRunState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_homerun"));

	//�׸��� ��ġ
	_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
	_player->_shadow->setY(_player->getY() + 90);

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = _count2 = 0;

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