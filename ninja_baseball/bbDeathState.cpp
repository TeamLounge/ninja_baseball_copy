#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbAttackPunchState.h"
#include "bbDamagedState.h"
#include "bbDeathState.h"

bbState * bbDeathState::inputHandle(blueBaseball * blueBaseball)
{
	return nullptr;
}

void bbDeathState::update(blueBaseball * blueBaseball)
{
	frameCount++;
	if (frameCount >= 15)		//한 번 모션 주고 끝나
	{
		frameCount = 0;
		if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
		{
			blueBaseball->setCurrentFrameX(blueBaseball->_blueBaseball.img->getMaxFrameX());
		}
		else
		{
			blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);
		}
	}
}

void bbDeathState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_spin");
	blueBaseball->setImageName("bBaseball_spin");
	if (!blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(1);
	}
	if (blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(0);
	}
	blueBaseball->setCurrentFrameX(0);
}

void bbDeathState::exit(blueBaseball * blueBaseball)
{
}
