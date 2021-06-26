#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"

ybState * ybMoveState::inputHandle(yellowBaseball * yellowBaseball)
{
	return nullptr;
}

void ybMoveState::update(yellowBaseball * yellowBaseball)
{
	frameCount++;
	if (frameCount >= 14)
	{
		frameCount = 0;
		if (yellowBaseball->_yellowBaseball.img->getFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
		{
			yellowBaseball->_yellowBaseball.img->setFrameX(-1);	//¹¹Áö ÀÌ°Å
		}
		yellowBaseball->_yellowBaseball.img->setFrameX(yellowBaseball->_yellowBaseball.img->getFrameX() + 1);
		yellowBaseball->_yellowBaseball.img->setFrameY(0);
	}
}

void ybMoveState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_move");
	yellowBaseball->_yellowBaseball.img->setFrameX(0);
	yellowBaseball->_yellowBaseball.img->setFrameY(0);

	return;
}

void ybMoveState::exit(yellowBaseball * yellowBaseball)
{
}
