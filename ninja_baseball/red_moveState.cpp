#include "stdafx.h"
#include "red_moveState.h"
#include "red_idleState.h"
#include "red_jumpState.h"
#include "red_attackState.h"
#include "red_runState.h"
#include "red_gripState.h"
#include "red_damage1State.h"
#include "red_catchState.h"

playerstate* red_moveState::handleInput(player* _player)
{
	if ((KEYMANAGER->isOnceKeyUp(VK_LEFT) && _runTime > 3) || (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _runTime > 3) ||
		KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		return new red_idleState;
	}

	if (KEYMANAGER->isOnceKeyDown('C')) //점프
	{
		return new red_jumpState;
	}

	if (KEYMANAGER->isOnceKeyDown('Z')) //점프 공격
	{
		return new red_attackState; 
	}

	if ((KEYMANAGER->isOnceKeyDown(VK_LEFT) && _isRun == true && _isLeft)
		|| KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _isRun == true && _isRight) //달리기
	{
		return new red_runState;
	}

	if (KEYMANAGER->isStayKeyDown('Z')) //잡으려고 준비하는 자세??
	{
		return new red_gripState;
	}

	if (_player->isdamage) //에너미에게 맞았을 떄
	{
		return new red_damage1State;
	}

	if (_player->iscatch) //에너미를 잡았을 때
	{
		return new red_catchState;
	}
	
	return nullptr;
}

void red_moveState::update(player * _player)
{
	
	/*if (_player->getRect().left < CAMERAMANAGER->getCameraLEFT())
	{
		_player->setX(_player->getX() + CAMERAMANAGER->getCameraLEFT() - _player->getRect().left);
	}
	*/

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->setX(_player->getX() - redSpeed);
		_player->isRight = false;
		_isLeft = true;
		_runTimeStart = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player->isRight = false;
		_runTimeStart = true;
	}


	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->setX(_player->getX() + redSpeed);
		_player->isRight = true;
		_isRight = true;
		_runTimeStart = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player->isRight = true;
		_runTimeStart = true;
	}

	
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->_shadow->getY() > 344)
	{
		_player->setY(_player->getY() - redSpeed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->_shadow->getY() < 617)
	{
		_player->setY(_player->getY() + redSpeed);
	}

	if (_runTimeStart)
	{
		_runTime++;
	}

	if (_runTime < 3)
	{
		_isRun = true;
	}

	_count++;

	if (_count % 5 == 0)
	{
		if (_player->isRight == true)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(0);

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}
		if (_player->isRight == false)
		{
			_index++;
			_player->getImage()->setFrameX(_index);
			_player->getImage()->setFrameY(1);

			if (_player->getImage()->getMaxFrameX() <= _player->getImage()->getFrameX())
			{
				_index = 0;
			}
			_count = 0;
		}
		
	}

	//그림자 위치
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		_player->_shadow->setX(_player->getX());
		_player->_shadow->setY(_player->getY());
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		_player->_shadow->setX(_player->getX());
		_player->_shadow->setY(_player->getY());
	}
	
	/*_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
		_player->getImage()->getFrameHeight());*/
	

	if (_player->isRight == true) //오른쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() + 10, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}
	if (_player->isRight == false) //왼쪽방향일때 렉트상태
	{
		_rc = RectMakeCenter(_player->getX() - 10, _player->getY(), 130, _player->getImage()->getFrameHeight());
	}

	_player->setRect(_rc);

}

void red_moveState::enter(player * _player)
{
	_player->setImage(IMAGEMANAGER->findImage("red_walk"));
	_player->setImageName("red_walk");
	
	//_rc = RectMakeCenter(_player->getX(), _player->getY(), _player->getImage()->getFrameWidth(),
	//	_player->getImage()->getFrameHeight());
	//_player->setRect(_rc);

	_count = _index = 0;
	_runTime = 0;
	_runTimeStart = false;
	_isRun = false;
	_isRight = false;
	_isLeft = false;

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
	if (_player->isRight == true)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 5 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		_player->_shadow->setX(_player->getX());
		_player->_shadow->setY(_player->getY());
	}
	if (_player->isRight == false)
	{
		_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		_player->_shadow->setX(_player->getX());
		_player->_shadow->setY(_player->getY());
	}
	
}
