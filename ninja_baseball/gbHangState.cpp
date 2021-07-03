#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbHangState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->_greenBaseball.rc.bottom >= greenBaseball->_greenBaseball.rcStop.top)
	{
		return new gbLandState();
	}
	return nullptr;
}

void gbHangState::update(greenBaseball * greenBaseball)
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

	gbStart(greenBaseball);
}

void gbHangState::enter(greenBaseball * greenBaseball)
{
	//플레이어가 특정 좌표에 오면 그 때, 인터벌 주고 등장
	if (true)
	{

	}
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_hang");
	greenBaseball->setImageName("gBaseball_hang");

	greenBaseball->setCurrentFrameX(0);
	greenBaseball->setCurrentFrameY(1);

	//greenBaseball->isattack = false;	//내려오는 동안은 안 맞게 여기서 꺼주자
}

void gbHangState::exit(greenBaseball * greenBaseball)
{
}

void gbHangState::gbStart(greenBaseball * greenBaseball)
{
	RECT temp;

	if (!(IntersectRect(&temp, &greenBaseball->_greenBaseball.rc, &greenBaseball->_greenBaseball.rcStop)))		//등장 충돌씬
	{
		greenBaseball->_greenBaseball.y += speed;
	}
}
