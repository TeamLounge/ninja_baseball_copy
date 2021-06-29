#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"

batState * batMoveState::inputHandle(bat * bat)
{
	//등장 후 일정 시간 지나면.. 상태 변경
	timeCount++;
	if (timeCount >= 150)
	{
		return new batIdleState();
	}

	return nullptr;
}

void batMoveState::update(bat * bat)
{
	if (!bat->isRight)	//왼쪽 보면
	{
		frameCount++;
		if (frameCount >= 8)
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
			bat->_bat.x -= 1.2f;
		}
		//감지 범위 => 왼쪽으로 생김
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 100, bat->_bat.y + 200, 250, 50);
	}
	if (bat->isRight)	//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 8)
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
			bat->_bat.x += 1.2f;
		}
		//감지 범위 => 왼쪽으로 생김
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 520, bat->_bat.y + 200, 250, 50);
	}
	//move (up, down)
	if (!bat->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!bat->isDown)	//위쪽이면
		{
			bat->_bat.y -= 1.2f;
		}
		if (bat->isDown)	//아래쪽이면
		{
			bat->_bat.y += 1.2f;
		}
	}
}

void batMoveState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_move");			//sBat, tBat때는 어떻게 해줘야할까..
	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

	//초기 등장하자마자 바로 timeCount 증가
	timeCount++;

}

void batMoveState::exit(bat * bat)
{
}
