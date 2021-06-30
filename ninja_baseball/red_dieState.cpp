#include "stdafx.h"
#include "red_dieState.h"

playerstate * red_dieState::handleInput(player * _player)
{
	return nullptr;
}

void red_dieState::update(player * _player)
{
	if (_rotation < 4)
	{
		_count++;

		if (_count % 5 == 0)
		{
			if (_player->isRight == true)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(0);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_rotation++;
					_index = 0;
				}
			}
			if (_player->isRight == false)
			{
				_player->getImage()->setFrameX(_index);
				_player->getImage()->setFrameY(1);
				_index++;

				if (_player->getImage()->getMaxFrameX() < _index)
				{
					_rotation++;
					_index = 0;
				}
			}

			_count = 0;
		}
	}
	
	
	
	
	//그림자 위치
	if (_player->isRight == true)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5);
		_player->_shadow->setY(_player->getY() + 90);
	}
	if (_player->isRight == false)
	{
		_player->_shadow->setX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15);
		_player->_shadow->setY(_player->getY() + 90);
	}
}

void red_dieState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_damage3"));

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = _time = 0;
	_rotation = 0;
	
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
