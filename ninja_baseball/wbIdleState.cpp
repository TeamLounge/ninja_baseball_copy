#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbRollState.h"
#include "wbStopState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbIdleState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (whiteBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 70)
		{
			timeCount = 0;
			return new wbAttackPunchState();
		}
	}
	else
	{	
		timeCount = 0;
	}
	return nullptr;
}

void wbIdleState::update(whiteBaseball * whiteBaseball)
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
				whiteBaseball->setCurrentFrameX(0);
			}
			else {
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);

			}
			whiteBaseball->setCurrentFrameY(1);
		}

		//move
		if (!whiteBaseball->isXOverlap)
		{
			whiteBaseball->_whiteBaseball.x -= 0.7f;
		}
		//감지 범위 => 왼쪽으로 생김
		whiteBaseball->_whiteBaseball.rcAttackRange = RectMakeCenter(whiteBaseball->_whiteBaseball.x, whiteBaseball->_whiteBaseball.y + 200, 250, 50);

	}
	if (whiteBaseball->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameX(0);
			}
			else 
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);

			}
			whiteBaseball->setCurrentFrameY(0);
		}
		//move
		if (!whiteBaseball->isXOverlap)
		{
			whiteBaseball->_whiteBaseball.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		whiteBaseball->_whiteBaseball.rcAttackRange = RectMakeCenter(whiteBaseball->_whiteBaseball.x + 360, whiteBaseball->_whiteBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!whiteBaseball->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!whiteBaseball->isDown)	//위쪽이면
		{
			whiteBaseball->_whiteBaseball.y -= 0.7f;
		}
		if (whiteBaseball->isDown)	//아래쪽이면
		{
			whiteBaseball->_whiteBaseball.y += 0.7f;
		}
	}
}

void wbIdleState::enter(whiteBaseball * whiteBaseball)		//init
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_idle");
	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}
	whiteBaseball->setCurrentFrameX(0);

	timeCount = 0;

	whiteBaseball->setImageName("wBaseball_idle");
}

void wbIdleState::exit(whiteBaseball * whiteBaseball)
{
}
