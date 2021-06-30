#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbLandState.h"
#include "bbAttackPunchState.h"
#include "bbDamagedState.h"
#include "bbDeathState.h"

bbState * bbIdleState::inputHandle(blueBaseball * blueBaseball)
{
	if (blueBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 60)
		{
			timeCount = 0;
			return new bbAttackPunchState();
		}
	}
	else
	{
		timeCount = 0;
	}
				
	return nullptr;
}

void bbIdleState::update(blueBaseball * blueBaseball)
{
	if (!blueBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else 
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);

			}
			blueBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		if (!blueBaseball->isXOverlap)
		{
			blueBaseball->_blueBaseball.x -= 0.7f;
		}
		//탐지 범위 왼쪽으로
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}
	if (blueBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);

			}
			blueBaseball->setCurrentFrameY(0);

		}
		//move
		if (!blueBaseball->isXOverlap)
		{
			blueBaseball->_blueBaseball.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x + 360, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!blueBaseball->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!blueBaseball->isDown)	//위쪽이면
		{
			blueBaseball->_blueBaseball.y -= 0.7f;
		}
		if (blueBaseball->isDown)	//아래쪽이면
		{
			blueBaseball->_blueBaseball.y += 0.7f;
		}
	}
}

void bbIdleState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_idle");
	if (!blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(1);
	}
	if (blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(0);
	}
	blueBaseball->setCurrentFrameX(0);

	timeCount = 0;

	blueBaseball->setImageName("bBaseball_idle");
}

void bbIdleState::exit(blueBaseball * blueBaseball)
{
}
