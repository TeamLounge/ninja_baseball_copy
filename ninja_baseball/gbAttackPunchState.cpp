#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbAttackPunchState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())	//펀치 프레임이 다 돌고 나면		//나중에 특정 조건 또 추가해주자 ex) 펀치 날렸고 + 맞으면, 안맞으면
	{
		greenBaseball->isattack = false;
		return new gbIdleState();	//디폴트(안맞으면)로 idle 상태
	}

	if (greenBaseball->isDeath)
	{
		return new gbDeathState();
	}

	return nullptr;
}

void gbAttackPunchState::update(greenBaseball * greenBaseball)
{
	if (!greenBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		greenBaseball->_greenBaseball.x -= 0.7f;
		//탐지 범위 왼쪽으로
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}
	if (greenBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(0);

		}
		//move
		greenBaseball->_greenBaseball.x += 0.7f;
		//감지 범위 => 오른쪽으로 생김
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x + 360, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!greenBaseball->isDown)	//위쪽이면
	{
		greenBaseball->_greenBaseball.y -= 0.7f;
	}
	if (greenBaseball->isDown)	//아래쪽이면
	{
		greenBaseball->_greenBaseball.y += 0.7f;
	}
}

void gbAttackPunchState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->isattack = true;
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_punch");
	greenBaseball->setImageName("gBaseball_punch");

	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	greenBaseball->isattack = true;
}

void gbAttackPunchState::exit(greenBaseball * greenBaseball)
{
}
