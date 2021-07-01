#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"
#include "wbDamagedState.h"
#include "wbDeathState.h"

wbState * wbDeathState::inputHandle(whiteBaseball * whiteBaseball)
{
	return nullptr;
}

void wbDeathState::update(whiteBaseball * whiteBaseball)
{
	frameCount++;
	if (frameCount >= 15)		//한 번 모션 주고 끝나
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
	}
}

void wbDeathState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_spin");
	whiteBaseball->setImageName("wBaseball_spin");

	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}
	whiteBaseball->setCurrentFrameX(0);
}

void wbDeathState::exit(whiteBaseball * whiteBaseball)
{
}
