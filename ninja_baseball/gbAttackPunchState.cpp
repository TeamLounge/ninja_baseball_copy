#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"

gbState * gbAttackPunchState::inputHandle(greenBaseball * greenBaseball)
{
	if (_currentFrameX == greenBaseball->_greenBaseball.img->getMaxFrameX())	//펀치 프레임이 다 돌고 나면		//나중에 특정 조건 또 추가해주자 ex) 펀치 날렸고 + 맞으면, 안맞으면
	{
		return new gbIdleState();	//디폴트(안맞으면)로 idle 상태
	}
	return nullptr;
}

void gbAttackPunchState::update(greenBaseball * greenBaseball)
{
	if (!greenBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}

		//왼쪽으로 이동
		greenBaseball->_greenBaseball.x -= 0.7f;
		//탐지 범위 왼쪽으로
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}
	if (greenBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else
			{
				_currentFrameX++;

			}
			_currentFrameY = 0;

		}
		//move
		greenBaseball->_greenBaseball.x += 0.7f;
		//감지 범위 => 오른쪽으로 생김
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x + 360, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!greenBaseball->isDown)	//위쪽이면
	{
		greenBaseball->_greenBaseball.y -= 0.7f;
	}
	if (greenBaseball->isDown)	//아래쪽이면
	{
		greenBaseball->_greenBaseball.y += 0.7f;
	}
}

void gbAttackPunchState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_punch");
	if (!greenBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (greenBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

}

void gbAttackPunchState::exit(greenBaseball * greenBaseball)
{
}
