#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDeathState::inputHandle(glove * glove)
{
	//죽음 상태
	//죽음 이미지 알파렌더
	//이후 deathRing 위로
	return nullptr;
}

void gloveDeathState::update(glove * glove)
{
	if (!glove->isRight)		//왼쪽 바라보면
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
			{
				glove->setCurrentFrameX(0);
			}
			else
			{
				glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);

			}
			glove->setCurrentFrameY(1);
		}

		//move
		if (!glove->isXOverlap)
		{
			glove->_glove.x -= 0.7f;
		}
		//감지 범위 => 왼쪽으로 생김
		glove->_glove.rcAttackRange = RectMakeCenter(glove->_glove.x, glove->_glove.y + 200, 250, 50);

	}
	if (glove->isRight)			//오른쪽 바라보면
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
			{
				glove->setCurrentFrameX(0);
			}
			else
			{
				glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);

			}
			glove->setCurrentFrameY(0);

		}
		//move
		if (!glove->isXOverlap)
		{
			glove->_glove.x += 0.7f;
		}
		//감지 범위 => 오른쪽으로 생김
		glove->_glove.rcAttackRange = RectMakeCenter(glove->_glove.x + 360, glove->_glove.y + 200, 250, 50);
	}

	//move (up, down)
	if (!glove->isYOverlap)//떨림방지	//isOverlap이 false일 때.. 즉, 구간 밖일 때(평소)	//반대로 중점이 구간 내라면 그 땐 y좌표는 움직이지 않는다.
	{
		if (!glove->isDown)	//위쪽이면
		{
			glove->_glove.y -= 0.7f;
		}
		if (glove->isDown)	//아래쪽이면
		{
			glove->_glove.y += 0.7f;
		}
	}
}

void gloveDeathState::enter(glove * glove)
{
}

void gloveDeathState::exit(glove * glove)
{
}
