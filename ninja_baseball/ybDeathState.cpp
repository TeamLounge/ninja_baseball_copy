#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybDeathState::inputHandle(yellowBaseball * yellowBaseball)
{
	if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
	{
		count++;
		if (count >= 8)
		{
			count = 0;
			yellowBaseball->isDeathDeleteState = true;
			/*RENDERMANAGER->deleteObj("card", 0);*/
		}
	}
	return nullptr;
}

void ybDeathState::update(yellowBaseball * yellowBaseball)
{
	frameCount++;
	if (frameCount >= 15)		//한 번 모션 주고 끝나
	{
		frameCount = 0;
		if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
		{
			yellowBaseball->setCurrentFrameX(yellowBaseball->_yellowBaseball.img->getMaxFrameX());
		}
		else
		{
			yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);
		}
	}
}

void ybDeathState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_spin");
	yellowBaseball->setImageName("yBaseball_spin");

	if (!yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(1);
	}
	if (yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(0);
	}
	yellowBaseball->setCurrentFrameX(0);

	yellowBaseball->isCollisionDamaged = true;
	yellowBaseball->isDeath = false;
}

void ybDeathState::exit(yellowBaseball * yellowBaseball)
{
}
