#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbLandState.h"
#include "bbAttackPunchState.h"
#include "bbDamagedState.h"
#include "bbDeathState.h"

bbState * bbAttackPunchState::inputHandle(blueBaseball * blueBaseball)
{
	if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())	//펀치 프레임이 다 돌고 나면		//나중에 특정 조건 또 추가해주자 ex) 펀치 날렸고 + 맞으면, 안맞으면
	{
		blueBaseball->isattack = false;
		return new bbIdleState();	//디폴트(안맞으면)로 idle 상태
	}

	return nullptr;
}

void bbAttackPunchState::update(blueBaseball * blueBaseball)
{
	if (!blueBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else 
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);

			}
			blueBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		blueBaseball->_blueBaseball.x -= 0.7f;
		//탐지 범위 왼쪽으로
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}
	if (blueBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);
			}
			blueBaseball->setCurrentFrameY(0);

		}
		//move
		blueBaseball->_blueBaseball.x += 0.7f;
		//감지 범위 => 오른쪽으로 생김
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x + 360, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!blueBaseball->isDown)	//위쪽이면
	{
		blueBaseball->_blueBaseball.y -= 0.7f;
	}
	if (blueBaseball->isDown)	//아래쪽이면
	{
		blueBaseball->_blueBaseball.y += 0.7f;
	}
}

void bbAttackPunchState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->isattack = true;
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_punch");
	if (!blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(1);
	}
	if (blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(0);
	}
	blueBaseball->setCurrentFrameX(0);
}

void bbAttackPunchState::exit(blueBaseball * blueBaseball)
{
}
