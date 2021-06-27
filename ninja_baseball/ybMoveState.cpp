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
		if (_currentFrameX == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else {
			_currentFrameX++;

		}
		_currentFrameY = 1;
	}
}

void ybMoveState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_move");
	_currentFrameX = 0;
	_currentFrameY = 1;

	return;
}

void ybMoveState::exit(yellowBaseball * yellowBaseball)
{
}
