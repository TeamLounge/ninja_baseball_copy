#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"

ybState * ybMoveState::inputHandle(yellowBaseball * yellowBaseball)
{
	//타격 범위에 들어오면 
	if (yellowBaseball->isCollisionAttack)
	{
		return new ybIdleState();
	}
	return nullptr;
}

void ybMoveState::update(yellowBaseball * yellowBaseball)
{
	frameCount++;
	if (frameCount >= 8)
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
}

void ybMoveState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_move");
	yellowBaseball->setCurrentFrameX(0);
	yellowBaseball->setCurrentFrameY(1);

	return;
}

void ybMoveState::exit(yellowBaseball * yellowBaseball)
{
}
