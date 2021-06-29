#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"
#include "batDeathState.h"

batState * batDamagedState::inputHandle(bat * bat)
{
	


	return nullptr;
}

void batDamagedState::update(bat * bat)
{
	if (!bat->isRight)		//왼쪽 바라보면
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
			{
				bat->setCurrentFrameX(0);
			}
			else
			{
				bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);

			}
			bat->setCurrentFrameY(1);
		}

		//move
		if (!bat->isXOverlap)
		{
			bat->_bat.x -= 0.7f;
		}
		//감지 범위 => 왼쪽으로 생김
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x, bat->_bat.y + 200, 250, 50);

	}
	if (bat->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
			{
				bat->setCurrentFrameX(0);
			}
			else
			{
				bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);

			}
			bat->setCurrentFrameY(0);

		}
		//move
		if (!bat->isXOverlap)
		{
			bat->_bat.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 360, bat->_bat.y + 200, 250, 50);
	}

	//move (up, down)
	if (!bat->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!bat->isDown)	//위쪽이면
		{
			bat->_bat.y -= 0.7f;
		}
		if (bat->isDown)	//아래쪽이면
		{
			bat->_bat.y += 0.7f;
		}
	}
}

void batDamagedState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_damaged");
	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

}

void batDamagedState::exit(bat * bat)
{
}
