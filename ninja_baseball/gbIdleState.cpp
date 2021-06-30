#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbIdleState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 60)
		{
			timeCount = 0;
			return new gbAttackPunchState();
		}
	}
	else
	{
		timeCount = 0;
	}
	return nullptr;
}

void gbIdleState::update(greenBaseball * greenBaseball)
{
	if (!greenBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else 
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		if (!greenBaseball->isXOverlap)
		{
			greenBaseball->_greenBaseball.x -= 0.7f;
		}
		//탐지 범위 왼쪽으로
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}
	if (greenBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(0);

		}
		//move
		if (!greenBaseball->isXOverlap)
		{
			greenBaseball->_greenBaseball.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x + 360, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!greenBaseball->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!greenBaseball->isDown)	//위쪽이면
		{
			greenBaseball->_greenBaseball.y -= 0.7f;
		}
		if (greenBaseball->isDown)	//아래쪽이면
		{
			greenBaseball->_greenBaseball.y += 0.7f;
		}
	}
}

void gbIdleState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_idle");
	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	timeCount = 0;

	greenBaseball->setImageName("gBaseball_idle");
}

void gbIdleState::exit(greenBaseball * greenBaseball)
{
}
