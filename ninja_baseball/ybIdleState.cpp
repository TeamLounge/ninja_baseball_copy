#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybIdleState::inputHandle(yellowBaseball * yellowBaseball)
{
	//떄리기
	if (yellowBaseball->isCollisionAttack)
	{
		yellowBaseball->timeCount++;
		if (yellowBaseball->timeCount >= 60)
		{
			yellowBaseball->timeCount = 0;
			return new ybAttackPunchState();
		}
	}
	else yellowBaseball->timeCount = 0;

	//맞기

	if (yellowBaseball->isCollisionDamaged)
	{
		yellowBaseball->damagedCount++;
		
		return new ybDamagedState();
	}
	return nullptr;
}

void ybIdleState::update(yellowBaseball * yellowBaseball)
{

	if (!yellowBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else 
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		if (!yellowBaseball->isXOverlap)
		{
			yellowBaseball->_yellowBaseball.x -= 0.7f;
		}
		//탐지 범위 왼쪽으로
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}
	if (yellowBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(0);

		}
		//move
		if (!yellowBaseball->isXOverlap)
		{
			yellowBaseball->_yellowBaseball.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x + 360, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!yellowBaseball->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!yellowBaseball->isDown)	//위쪽이면
		{
			yellowBaseball->_yellowBaseball.y -= 0.7f;
		}
		if (yellowBaseball->isDown)	//아래쪽이면
		{
			yellowBaseball->_yellowBaseball.y += 0.7f;
		}
	}
}

void ybIdleState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_idle");
	yellowBaseball->setImageName("yBaseball_idle");

	if (!yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(1);
	}
	if (yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(0);
	}
	yellowBaseball->setCurrentFrameX(0);

	yellowBaseball->timeCount = 0;
}

void ybIdleState::exit(yellowBaseball * yellowBaseball)
{
}
