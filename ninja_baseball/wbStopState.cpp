#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbStopState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (speed <= friction)
	{
		return new wbIdleState();
	}

	return nullptr;
}

void wbStopState::update(whiteBaseball * whiteBaseball)
{

	if (!whiteBaseball->isRight)		//왼쪽 바라보면
	{
		//frame
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				_currentFrameX = whiteBaseball->_whiteBaseball.img->getMaxFrameX();
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}
	}
	if (whiteBaseball->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				_currentFrameX = whiteBaseball->_whiteBaseball.img->getMaxFrameX();
			}
			else
			{
				_currentFrameX++;

			}
			_currentFrameY = 0;
		}
	}

	//뒤로 조금 밀림
	if (speed > friction)
	{
		if (whiteBaseball->isRight)
		{
			whiteBaseball->_whiteBaseball.x -= speed;
			speed -= friction;

		}
		if (!whiteBaseball->isRight)
		{
			whiteBaseball->_whiteBaseball.x += speed;
			speed -= friction;
		}
	}



}
void wbStopState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_stop");
	if (!whiteBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (whiteBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

	speed = 3.0f;
	friction = 0.07f;
}

void wbStopState::exit(whiteBaseball * whiteBaseball)
{
}
