#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybAttackPunchState::inputHandle(yellowBaseball * yellowBaseball)
{
	if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())	//펀치 프레임이 다 돌고 나면		//나중에 특정 조건 또 추가해주자 ex) 펀치 날렸고 + 맞으면, 안맞으면
	{
		yellowBaseball->isattack = false;
		return new ybIdleState();	//디폴트(안맞으면)로 idle 상태
	}
	return nullptr;
}

void ybAttackPunchState::update(yellowBaseball * yellowBaseball)
{
	if (!yellowBaseball->isRight)		//왼쪽 보고 있으면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else 
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(1);
		}

		//왼쪽으로 이동
		yellowBaseball->_yellowBaseball.x -= 0.7f;
		//탐지 범위 왼쪽으로
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}
	if (yellowBaseball->isRight)			//오른쪽 보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(0);

		}
		//move
		yellowBaseball->_yellowBaseball.x += 0.7f;
		//감지 범위 => 오른쪽으로 생김
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x + 360, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!yellowBaseball->isDown)	//위쪽이면
	{
		yellowBaseball->_yellowBaseball.y -= 0.7f;
	}
	if (yellowBaseball->isDown)	//아래쪽이면
	{
		yellowBaseball->_yellowBaseball.y += 0.7f;
	}
}

void ybAttackPunchState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->isattack = true;
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_punch");
	if (!yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(1);
	}
	if (yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(0);
	}
	yellowBaseball->setCurrentFrameX(0);

}

void ybAttackPunchState::exit(yellowBaseball * yellowBaseball)
{
}
