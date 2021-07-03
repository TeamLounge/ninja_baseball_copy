#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybMoveState::inputHandle(yellowBaseball * yellowBaseball)
{
	//등장
	timeCount++;
	if (timeCount >= 250)
	{
		return new ybIdleState();
	}

	return nullptr;
}

void ybMoveState::update(yellowBaseball * yellowBaseball)
{
	if (!yellowBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 17)
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
		if (frameCount >= 17)
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

	
}

void ybMoveState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_move");
	yellowBaseball->setImageName("yBaseball_move");

	yellowBaseball->setCurrentFrameX(0);
	yellowBaseball->setCurrentFrameY(1);

	timeCount = 0;
}

void ybMoveState::exit(yellowBaseball * yellowBaseball)
{
}
