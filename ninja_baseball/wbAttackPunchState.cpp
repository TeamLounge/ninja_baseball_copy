#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackPunchState.h"
#include "wbAttackJumpState.h"

wbState * wbAttackPunchState::inputHandle(whiteBaseball * whiteBaseball)
{	
	if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
	{
		whiteBaseball->isJump = true;	//���������� �˸�
		return new wbAttackJumpState();
	}

	return nullptr;
}

void wbAttackPunchState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
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
	if (whiteBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 15)
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

}

void wbAttackPunchState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_punch");
	if (!whiteBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (whiteBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;
}

void wbAttackPunchState::exit(whiteBaseball * whiteBaseball)
{
}
