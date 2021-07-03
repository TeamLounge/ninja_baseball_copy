#include "stdafx.h"
#include "red_catchAttackState.h"
#include "red_catchState.h"

playerstate * red_catchAttackState::handleInput(player * _player)
{
	if (_player->getImage()->getMaxFrameX() + 1 < _index)
	{
		_player->_isRedCatchAttackOn = false;
		return new red_catchState;
	}
	
	return nullptr;
}

void red_catchAttackState::update(player * _player)
{
	_count++;
	  
	if (_count % 8 == 0) 
	{
		if (_player->isRight == true)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);
			_index++;
		}
		if (_player->isRight == false)
		{
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);
			_index++;
		}

		_count = 0;
	}

	//공격할때 에너미랑 충돌한 렉트 생성
			//=========================================================
	if (_index == 2) 
	{
		_player->isattack = true;
		if (!_player->_isRedCatchAttack) _player->_isRedCatchAttack = true;
		
		if (_player->isRight == true)
		{
			_player->_attack_rc = RectMakeCenter(_player->getX() + _player->getImage()->getFrameWidth() / 2 - 50, _player->getY(), 70, 70);
		}
		if (_player->isRight == false)
		{
			_player->_attack_rc = RectMakeCenter(_player->getX() - _player->getImage()->getFrameWidth() / 2 + 50, _player->getY(), 70, 70);
		}
	}
	else
	{
		_player->isattack = false;
	}
	//=============================================================
		
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
}

void red_catchAttackState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_gripAttack"));
	_player->setImageName("red_gripAttack");

	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

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
