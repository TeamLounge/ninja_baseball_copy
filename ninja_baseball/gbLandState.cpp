#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbLandState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())	//그림자랑 충돌하면 idle로
	{
		return new gbIdleState();
	}
	return nullptr;
}

void gbLandState::update(greenBaseball * greenBaseball)
{
	frameCount++;
	if (frameCount >= 3)
	{
		frameCount = 0;
		if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
		{
			greenBaseball->setCurrentFrameX(0);
		}
		else {
			greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);
		}
		greenBaseball->setCurrentFrameY(1);
	}

	gbJump(greenBaseball);
}

void gbLandState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->isLand = true;	//도착했으니 그 때 그림자 켜주자
	greenBaseball->isJump = true;

	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_roll");
	greenBaseball->setImageName("gBaseball_roll");

	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	//초기화
	jumpPower = 19.0f;
	gravity = 1.28f;
}

void gbLandState::exit(greenBaseball * greenBaseball)
{
}

void gbLandState::gbJump(greenBaseball * greenBaseball)
{
	if (greenBaseball->isJump)
	{
		//중력주기
		greenBaseball->_greenBaseball.y -= jumpPower;
		jumpPower -= gravity;

		//x좌표 움직이기
				//오른쪽
		greenBaseball->_greenBaseball.x += 5;

		//y좌표 특정위치까지만 중력ON
		if ((greenBaseball->_gbShadow.rc.bottom + greenBaseball->_gbShadow.rc.top) / 2 < greenBaseball->_greenBaseball.rc.bottom) //그림자 넘어서면
		{
			greenBaseball->_greenBaseball.y -= greenBaseball->_greenBaseball.rc.bottom - (greenBaseball->_gbShadow.rc.bottom + greenBaseball->_gbShadow.rc.top) / 2;	//들어간만큼 빼준다.
			jumpPower = 0;
			gravity = 0;
			greenBaseball->isJump = false;
		}
	}
}
