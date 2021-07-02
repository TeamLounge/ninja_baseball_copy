#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDamagedState::inputHandle(glove * glove)
{
	if (glove->damagedCount == 5)
	{
		glove->damagedCount = 0;
		return new gloveDeathState();
	}
	if (glove->damagedCount < 5 && glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
	{
		glove->setCurrentFrameX(0);
		glove->isCollisionDamaged = false;
		return new gloveMoveState();
	}
	  
	return nullptr;
}

void gloveDamagedState::update(glove * glove)
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

void gloveDamagedState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_damaged");
	glove->setImageName("glove_damaged");

	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);

	//glove->isCollisionDamaged = true;

}

void gloveDamagedState::exit(glove * glove)
{
}







////////////////////////////////////////
//move->탐지범위ON->인터벌->계속 탐지범위->attack(때림)
//->인터벌->상대가 공격->맞음->isCollisionDamaged = true
//->damageCount++;
//if (damageCount < 5)
//	return new Damaged();->damageCount == 5 면 또 Death로 / ->아니고 5 아래면 move로
//	if (damageCount == 5)
//	{
//		return new Death();
//	}
//	else return new Move();
//
//탐지범위OFF->계속 붙어 갈거고
//
//
//
//
//
//<맞음> //상대 공격 시를 제외하곤 어디서나 맞을 수 있다(move일 때.. jump 충돌도 맞음)
//1. 플레이어 몸과 충돌 + M
//->isCollisionDamaged = true
//->damageCount++;
//if (damageCount == 5)
//{
//	return new Death();
//}
//else	return new Move();
//
//<때림>
//
