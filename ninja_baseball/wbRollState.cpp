#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"
#include "wbDamagedState.h"
#include "wbDeathState.h"


wbState * wbRollState::inputHandle(whiteBaseball * whiteBaseball)		//상태에 따른 변경들 추가하자. 상태끼리 왔다갔다 작용
{
	//Roll상태에서!!!!! 충돌 후 Stop으로
	RECT temp;
	if (IntersectRect(&temp, &whiteBaseball->_whiteBaseball.rc, &whiteBaseball->_whiteBaseball.rcStop))	
	{
		whiteBaseball->isRollState = false;
		return new wbStopState();
	}
	if (whiteBaseball->isDeath)
	{
		return new wbDeathState();
	}
	return nullptr;
}

void wbRollState::update(whiteBaseball * whiteBaseball)
{
	frameCount++;
	if (frameCount >= 8)
	{
		frameCount = 0;
		if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
		{
			whiteBaseball->setCurrentFrameX(0);
		}
		else {
			whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);
		}
		whiteBaseball->setCurrentFrameY(1);
	}

	wbStart(whiteBaseball);

}

void wbRollState::enter(whiteBaseball * whiteBaseball)	//init!!!!
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_roll");
	whiteBaseball->setImageName("wBaseball_roll");

	whiteBaseball->setCurrentFrameX(0);
	whiteBaseball->setCurrentFrameY(1);

	return;
}

void wbRollState::exit(whiteBaseball * whiteBaseball)
{
}

void wbRollState::wbStart(whiteBaseball * whiteBaseball)
{
	RECT temp;

	if (!(IntersectRect(&temp, &whiteBaseball->_whiteBaseball.rc, &whiteBaseball->_whiteBaseball.rcStop)))		//등장 충돌씬
	{
		whiteBaseball->_whiteBaseball.x -= speed;
	}
}
