#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackPunchState.h"
#include "wbAttackJumpState.h"

wbState * wbAttackPunchState::inputHandle(whiteBaseball * whiteBaseball)
{	
	if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
	{
		whiteBaseball->isattack = false;
		whiteBaseball->isJump = true;	//점프했음을 알림
		return new wbAttackJumpState();
	}

	return nullptr;
}

void wbAttackPunchState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//왼쪽 바라보면
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->_whiteBaseball.img->getMaxFrameX());
			}
			else {
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);
			}
			whiteBaseball->setCurrentFrameY(1);
		}
	}
	if (whiteBaseball->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->_whiteBaseball.img->getMaxFrameX());
			}
			else 
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);
			}
			whiteBaseball->setCurrentFrameY(0);
		}
	}
}

void wbAttackPunchState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->isattack = true;
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_punch");
	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}

	whiteBaseball->setCurrentFrameX(0);

	whiteBaseball->setImageName("wBaseball_punch");
	whiteBaseball->isattack = true;

}

void wbAttackPunchState::exit(whiteBaseball * whiteBaseball)
{
}
