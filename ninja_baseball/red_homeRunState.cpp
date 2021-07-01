#include "stdafx.h"
#include "red_homeRunState.h"
#include "red_idleState.h"

playerstate* red_homeRunState::handleInput(player* _player)
{
	if (_index > _player->getImage()->getMaxFrameX())
	{
		_player->setY(_player->getY() + 20);

		if (_player->isRight == true)
		{
			_player->setX(_player->getX() - 60);
		}
		if (_player->isRight == false)
		{
			_player->setX(_player->getX() + 60);
		}

		return new red_idleState;
	}

	return nullptr;
}

void red_homeRunState::update(player* _player)
{
	_count++;
	
	if (_count % 5 == 0)
	{
		_index++;

		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_count++;
		}
		
		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_count++;
		}
		
		if (_player->isRight == true)
		{
			if (_count2 < 5 && _index > 3)
			{
				_player->setX(_player->getX() + 50);
			}
		}

		if (_player->isRight == false)
		{
			if (_count2 < 5 && _index > 3)
			{
				_player->setX(_player->getX() - 50);
			}
		}

		//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
		if (_index == 3)
		{
			_player->isattack = true;

			if (_player->isRight == true)
			{
				_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 50, _player->getY(), 80, 80);
			}
			if (_player->isRight == false)
			{
				_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 50, _player->getY(), 80, 80);
			}
		}
		else
		{
			_player->isattack = false;
		}


		//그림자 위치
		if (_player->isRight == true)
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 70 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
			_player->setShadowY(_player->getY() + 110 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		}
		if (_player->isRight == false)
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 70 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
			_player->setShadowY(_player->getY() + 110 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		}
	}
}

void red_homeRunState::enter(player* _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_homerun"));
	_player->setImageName("red_homerun");
		
	_player->setY(_player->getY() + 20);
	if (_player->isRight == true)
	{
		_player->setX(_player->getX() + 60);
	}
	if (_player->isRight == false)
	{
		_player->setX(_player->getX() - 60);
	}

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