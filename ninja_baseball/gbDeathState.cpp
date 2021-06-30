#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbDeathState::inputHandle(greenBaseball * greenBaseball)
{
	return nullptr;
}

void gbDeathState::update(greenBaseball * greenBaseball)
{
	frameCount++;
	if (frameCount >= 15)		//한 번 모션 주고 끝나
	{
		frameCount = 0;
		if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
		{
			greenBaseball->setCurrentFrameX(greenBaseball->_greenBaseball.img->getMaxFrameX());
		}
		else
		{
			greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);
		}
	}
}

void gbDeathState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_spin");
	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);
}

void gbDeathState::exit(greenBaseball * greenBaseball)
{
}
