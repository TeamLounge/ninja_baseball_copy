#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"
#include "batDeathState.h"

batState * batAttackState::inputHandle(bat * bat)
{
	if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())		//한 동작 끝나면 idle로 가라
	{
		bat->isAttack = false;
		return new batIdleState();
	}
	if (bat->isDeath)
	{
		return new batDeathState();
	}
	return nullptr;
}

void batAttackState::update(bat * bat)
{
	if (!bat->isRight)
	{
		frameCount++;
		if (frameCount >= 4)
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
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 100, bat->_bat.y + 200, 250, 50);
	}

	if (bat->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 4)
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
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 460, bat->_bat.y + 200, 250, 50);
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

void batAttackState::enter(bat * bat)
{

	switch (bat->_batMode)
	{
	case NORMAL:
		bat->_bat.img = IMAGEMANAGER->findImage("fBat_attack");
		bat->setImageName("fBat_attack");
		break;
	case NO_CAP:
		bat->_bat.img = IMAGEMANAGER->findImage("sBat_attack");
		bat->setImageName("sBat_attack");
		break;
	case NO_BAT:
		bat->_bat.img = IMAGEMANAGER->findImage("tBat_attack");
		bat->setImageName("tBat_attack");
		break;
	case DEATH:
		bat->isDeath = true;
		break;
	default:
		break;
	}

	bat->isAttack = true;
	

	//attackCount = 0;

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

void batAttackState::exit(bat * bat)
{
}
