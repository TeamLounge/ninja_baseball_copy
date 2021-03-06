#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"
#include "wbDamagedState.h"
#include "wbDeathState.h"

wbState * wbAttackJumpState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isJump)
	{
		return new wbStopState();
	}
	if (whiteBaseball->isDeath)
	{
		return new wbDeathState();
	}


	return nullptr;
}

void wbAttackJumpState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//왼쪽 바라보면
	{
		//frame
		frameCount++;
		if (frameCount >= 4)
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
			whiteBaseball->setCurrentFrameY(1);
		}
	}
	if (whiteBaseball->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 4)
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
	}

	jump(whiteBaseball);


}

void wbAttackJumpState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_roll");
	whiteBaseball->setImageName("wBaseball_roll");
	
	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}
	whiteBaseball->setCurrentFrameX(0);

	//초기화
	jumpPower =21.0f;
	gravity = 0.58f;

	
}

void wbAttackJumpState::exit(whiteBaseball * whiteBaseball)
{
}

void wbAttackJumpState::jump(whiteBaseball * whiteBaseball)
{
	if (whiteBaseball->isJump)
	{
		//중력주기
		whiteBaseball->_whiteBaseball.y -= jumpPower;
		jumpPower -= gravity;

		//x좌표 움직이기
		if (!whiteBaseball->isRight)	//왼쪽
		{
			whiteBaseball->_whiteBaseball.x -= 5;
		}
		if (whiteBaseball->isRight)		//오른쪽
		{
			whiteBaseball->_whiteBaseball.x += 5;
		}

		//y좌표 특정위치까지만 중력ON
		if ((whiteBaseball->_wbShadow.rc.bottom + whiteBaseball->_wbShadow.rc.top) / 2 < whiteBaseball->_whiteBaseball.rc.bottom)
		{
			whiteBaseball->_whiteBaseball.y -= whiteBaseball->_whiteBaseball.rc.bottom - (whiteBaseball->_wbShadow.rc.bottom + whiteBaseball->_wbShadow.rc.top) / 2;
			jumpPower = 0;
			gravity = 0;
			whiteBaseball->isJump = false;
		}
	}
	
}
